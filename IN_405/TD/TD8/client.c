#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define DICT_PATH_PREFIX "/tmp"

/* print usage message and return nonnull rc */
int usage(const char* prog){
  fprintf(stderr,
          "[ERR] usage: %s dict action [opt1 opt2]\n"
          "             action: + name value\n"
          "                     - name\n"
          "                     ? name\n"
          "                     !\n",
          prog);

  return 1;
}

/* open a pipe for the given dictionary, input or output side */
int open_pipe(const char* dict_name,bool dict_input){
  char buf[256];
  int fd;

  sprintf(buf,"%s/dict_%s_%s",DICT_PATH_PREFIX,dict_name,dict_input ? "in" : "out");
  return open(buf,dict_input ? O_WRONLY | O_APPEND : O_RDONLY);
}

/* send add command to the server */
int dict_add(const char* dict_name,const char* value_name,double value){
  char buf[256];
  int rc,fd;
  int rc2 = 0;


  //open write pipe
  fd = open_pipe(dict_name,true);
  if (fd == -1){
    fprintf(stderr,"[ERR] on pipe openning of file descriptor %d: %s\n",fd,strerror(errno));
    rc2 = 1;
  }
  else{

    //construct request
    sprintf(buf,"+;%s;%f;",value_name,value);

    //send request
    rc = write(fd,buf,strlen(buf));
    if (rc == -1){
      fprintf(stderr,"[ERR] on request sending: %s\n",strerror(errno));
      rc2 = 1;
    }

    //close pipe
    rc = close(fd);
    if (rc){
      fprintf(stderr,"[ERR] on pipe closing: %s\n",strerror(errno));
      rc2 = 1;
    }
  }
  return rc2;
}

/* send remove commant to the server */
int dict_remove(const char* dict_name,const char* value_name){
  char buf[256];
  int rc,fd;
  int rc2 = 0;

  //open write pipe
  fd = open_pipe(dict_name,true);
  if (fd == -1){
    fprintf(stderr,"[ERR] on pipe openning of file descriptor %d: %s\n",fd,strerror(errno));
    rc2 = 1;
  }
  else{

    //constructor request
    sprintf(buf,"-;%s;",value_name);

    //send request
    rc = write(fd,buf,strlen(buf));
    if (rc == -1){
      fprintf(stderr,"[ERR] on request sending: %s\n",strerror(errno));
      rc2 = 1;
    }

    //close pipe
    rc = close(fd);
    if (rc){
      fprintf(stderr,"[ERR] on pipe closing: %s\n",strerror(errno));
      rc2 = 1;
    }
  }
  return rc2;
}

/* send ask command to the server */
int dict_ask(const char* dict_name,const char* value_name){
  char buf[256];
  char value[64];
  int rc,count,offset,dummy,wait,fd,error,state,index;
  double value_decoded;
  int rc2 = 0;

  count = 0;offset = 0;wait = 1;state = 0;index = 0;value_decoded = 0;

  //open write pipe
  fd = open_pipe(dict_name,true);
  if (fd == -1){
    fprintf(stderr,"[ERR] on pipe openning of file descriptor %d: %s\n",fd,strerror(errno));
    rc2 = 1;
  }

  //if pipe is open
  if (fd >= 0){

    //constructor request
    sprintf(buf,"?;%s;",value_name);

    //send request
    rc = write(fd,buf,strlen(buf));
    if (rc == -1){
      fprintf(stderr,"[ERR] on request sending: %s\n",strerror(errno));
      rc2 = 1;
    }

    //close pipe
    rc = close(fd);
    if (rc){
      fprintf(stderr,"[ERR] on pipe closing of file descriptor %d: %s\n",fd,strerror(errno));
      rc2 = 1;
    }

    //open read pipe
    fd = open_pipe(dict_name,false);
    if (fd == -1){
      fprintf(stderr,"[ERR] on pipe openning of file descriptor %d: %s\n",fd,strerror(errno));
      rc2 = 1;
    }
    else{

      //try to read input pipe to set offset at end of the file
      do{
        count = read(fd,&dummy,1);
        if (count > 0){
          offset++;
        }
      }
      while (count > 0);

      lseek(fd,offset,SEEK_SET);

      //read pipe for response
      memset(buf,0,sizeof(buf));
      offset = 0;
      do{
        count = read(fd,&buf[offset],1);
        if (count > 0){
          offset++;
          wait = 0;
        }
      }
      while((count > 0) || (wait == 1));

      //close read pipe
      rc = close(fd);
      if (rc){
        fprintf(stderr,"[ERR] on pipe closing of file descriptor %d: %s\n",fd,strerror(errno));
        rc2 = 1;
      }

      //interpret data
      count = 0;
      do{
        if (buf[count] == ';'){
          switch(state){
            case 0:
            error = atoi(value);
            index = 0;
            memset(value,0,sizeof(value));
            state++;
            break;

            case 1:
            value_decoded = strtod(value,NULL);
            state++;
            break;
          }
        }
        else{
          switch(state){
            case 0:
            value[index] = buf[count];
            index++;
            break;

            case 1:
            value[index] = buf[count];
            index++;
            break;
          }
        }
        count++;
      }
      while (count < offset);

      if (error){
        fprintf(stderr,"[ERR] Server was not able to provide data for this key.\n");
        rc2 = 1;
      }
      else{
        fprintf(stderr,"[INF] Response for data %s: %f\n\n",value_name,value_decoded);
      }
    }
  }
  return rc2;
}

/* send exit command to the server */
int dict_exit(const char* dict_name){
  char buf[256];
  int rc,fd;
  int rc2 = 0;

  //open pipe
  fd = open_pipe(dict_name,true);
  if (fd == -1){
    fprintf(stderr,"[ERR] on pipe openning of file decriptor %d: %s\n",fd,strerror(errno));
    rc2 = 1;;
  }
  else{

    //constructor request
    sprintf(buf,"!;");

    //send request
    rc = write(fd,buf,strlen(buf));
    if (rc == -1){
      fprintf(stderr,"[ERR] on request sending: %s\n",strerror(errno));
      rc2 = 1;
    }

    //close pipe
    rc = close(fd);
    if (rc){
      fprintf(stderr,"[ERR] on pipe closing: %s\n",strerror(errno));
      rc2 = 1;
    }
  }
  return rc2;
}

/* client main function, literally parse the program args
 * and then send the command to the desired server */
int main(int argc,char** argv){

  if (argc < 3) return usage(argv[0]);

  if (strcmp(argv[2], "+") == 0){
      if (argc != 5) return usage(argv[0]);
      return dict_add(argv[1],argv[3],strtod(argv[4],NULL));

  } else if (strcmp(argv[2],"-") == 0){
      if (argc != 4) return usage(argv[0]);
      return dict_remove(argv[1],argv[3]);

  } else if (strcmp(argv[2],"?") == 0){
      if (argc != 4) return usage(argv[0]);
      return dict_ask(argv[1],argv[3]);

  } else if (strcmp(argv[2],"!") == 0){
      if (argc != 3) return usage(argv[0]);
      return dict_exit(argv[1]);
    }
    return usage(argv[0]);
}
