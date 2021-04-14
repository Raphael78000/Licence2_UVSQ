#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define DICT_NAME_MAX 64
#define DICT_PATH_PREFIX "/tmp"
#define FILE_PERMISSIONS 0666

/* entry of a dictionary, consists in a name and its value */
struct dictionary_item{
    char name[DICT_NAME_MAX];
    double value;
};

/* operators of a dictionary */
enum command_op{
  OP_NONE,    /* no command*/
  OP_ADD,     /* add an entry */
  OP_REMOVE,  /* remove an entry */
  OP_ASK,     /* ask about an entry */
  OP_EXIT     /* terminate server */
};

/* command extracted from the input pipe */
struct command{
    enum command_op op;
    char name[DICT_NAME_MAX];
    double value;
};

/* allocate the dictionary structure */
int create_dict(const char *size_string, struct dictionary_item **dict,size_t *dict_max_size){
  int size_dict;

  //convert size in string into int
  *dict_max_size = atoi(size_string);

  //allocate memory for dictionary_item
  *dict = malloc(sizeof(struct dictionary_item) * (*dict_max_size));

  //initialise dictionary
  memset(*dict,0,sizeof(struct dictionary_item) * *dict_max_size);

  //creation of dictionary was successfull
  if (dict != NULL){
    return 0;
  }

  //creation of dictionary has failed
  else{
    return 1;
  }
 }

/* free the dictionary structure */
void destroy_dict(struct dictionary_item* dict){
  //free allocated memory for dictionary
  free(dict);
}

/* create the pipe files used by the server */
int create_pipes(const char* dict_name){
  char buf[256];
  int fd,rc;
  int rc2 = 0;

  //create & open file for output commands then close it
  sprintf(buf,"%s/dict_%s_out",DICT_PATH_PREFIX,dict_name);
  fd = open(buf,O_CREAT,FILE_PERMISSIONS);
  if (fd == -1){
    fprintf(stderr,"[ERR] on file creation: %s\n",strerror(errno));
    rc2 = 1;
  }
  else{
    rc = close(fd);
    if (rc){
      fprintf(stderr,"[ERR] on file closing: %s\n",strerror(errno));
      rc2 = 1;
    }
  }

  //create & open file for input commands then close it
  sprintf(buf,"%s/dict_%s_in",DICT_PATH_PREFIX,dict_name);
  fd = open(buf,O_CREAT,FILE_PERMISSIONS);
  if (fd == -1){
    fprintf(stderr,"[ERR] on file closing: %s\n",strerror(errno));
    rc2 = 1;
  }
  else{
    rc = close(fd);
    if (rc){
      fprintf(stderr,"[ERR] on file closing: %s\n",strerror(errno));
      rc2 = 1;
    }
  }
  return rc2;
}

/* destroy the pipe files used by the server */
void destroy_pipes(const char* dict_name){
  char buf[256];
  int rc;

  //remove file for output commands
  sprintf(buf,"%s/dict_%s_out",DICT_PATH_PREFIX,dict_name);
  rc = unlink(buf);
  if (rc){
    fprintf(stderr,"[ERR] on file removing: %s\n",strerror(errno));
  }

  //remove file for input commands
  sprintf(buf,"%s/dict_%s_in",DICT_PATH_PREFIX,dict_name);

  rc = unlink(buf);
  if (rc){
    fprintf(stderr,"[ERR] on file removing: %s\n",strerror(errno));
  }
}

/* open a pipe for the given dictionary, input or output side */
int open_pipe(const char* dict_name,bool dict_input,int offset){
  char buf[256];
  int fd;

  sprintf(buf,"%s/dict_%s_%s",DICT_PATH_PREFIX,dict_name,dict_input ? "in" : "out");
  fd = open(buf,dict_input ? O_RDONLY : (O_WRONLY | O_APPEND));
  if ((fd >= 0) && (dict_input)){
    lseek(fd,offset,SEEK_SET);
  }
  return fd;
}

/* close a pipe */
void close_pipe(int fd){
  int rc;

  rc = close(fd);
  if (rc){
    fprintf(stderr,"[ERR] on file closing of file descriptor %d: %s\n",fd,strerror(errno));
  }
}

/* receive a command from the input pipe */
int receive_command(int fd,struct command* cmd,int* offset){
  char buf[256];
  char value[64];
  int index,index2,state,size,rc;
  int rc2 = 0;

  size = 0;index = 0;

  cmd->op = OP_NONE;

  //read file byte per byte until end is reached
  do{
    rc = read(fd,&buf[size],1);
    if (rc > 0){
      size++;
    }
  }
  while ((rc > 0) && (size < sizeof(buf)));

  if (rc < 0){
    fprintf(stderr,"[ERR] on file reading descriptor %d: %s\n",fd,strerror(errno));
    rc2 = 1;
  }
  else{
    *offset = *offset + size;
    index = 0;
    index2 = 0;
    state = 0;

    memset(cmd->name,0,sizeof(value));
    memset(value,0,sizeof(value));

    //decode the data
    while (index < size){
      if (buf[index] == ';'){
        switch(state){
          case 0:
          //nothing to do
          break;

          case 1:
          index2 = 0;
          break;

          case 2:
          cmd->value = strtod(value,NULL);
          break;

          default:
          //potential remaining data is ignored
          break;
        }
        state++;
      }
      else{
        switch(state){
          case 0:
          if (buf[index] == '+'){
            cmd->op = OP_ADD;
          }
          else if (buf[index] == '-'){
            cmd->op = OP_REMOVE;
          }
          else if (buf[index] == '?'){
            cmd->op = OP_ASK;
          }
          else if (buf[index] == '!'){
            cmd->op = OP_EXIT;
          }
          //else do nothing
          break;

          case 1:
          cmd->name[index2] = buf[index];
          index2++;
          break;

          case 2:
          value[index2] = buf[index];
          index2++;
          break;

          default:
          //potential remaining data is ignored
          break;
        }
      }
      index++;
    }
  }
  return rc2;
}

/* add an entry to the dictionary */
int dict_add(struct dictionary_item* dict,size_t* dict_count,size_t dict_max_size,struct command cmd){
  int count,index;
  int rc = 0;

  count = *dict_count;

  //check that key is not already int doctionary
  for (index = 0;index < count;index++){
    if (strncmp(dict[index].name,cmd.name,DICT_NAME_MAX) == 0){
      break;
    }
  }

  if ((count < dict_max_size) && ((index >= count) || (count == 0))){
    strncpy(dict[count].name,cmd.name,DICT_NAME_MAX);
    dict[count].value = cmd.value;
    count++;
  }
  else{
    rc = 1;
  }

  *dict_count = count;

  return rc;
}

/* remove an entry from the dictionary */
int dict_remove(struct dictionary_item* dict,size_t* dict_count,struct command cmd){
  int index,index2,count;
  int rc = 0;

  count = *dict_count;

  //search index of the key
  for (index = 0;index < count;index++){
    if (strncmp(dict[index].name,cmd.name,DICT_NAME_MAX) == 0){
      break;
    }
  }

  if (index < count){
    for (index2 = index;index2 < (count - 1);index2++){
      //copy case n+1 into n
      memcpy(&dict[index2],&dict[index2 + 1],sizeof(struct dictionary_item));
    }
    count--;
  }
  else{
    rc = 1;
  }
  *dict_count = count;

  return rc;
}

/* ask the value of a dictionary entry, if exists */
int dict_ask(struct dictionary_item* dict,size_t dict_count,struct command* cmd){
  int index,index2;
  int rc = 0;

  //search index of the key
  for (index = 0;index < dict_count;index++){
    if (strncmp(dict[index].name,cmd->name,DICT_NAME_MAX) == 0){
      break;
    }
  }

  if (index < dict_count){
    strncpy(cmd->name,dict[index].name,DICT_NAME_MAX);
    cmd->value = dict[index].value;
  }
  else{
    rc = 1;
  }
  return rc;
}

/* send the response of an ask request */
int send_response(int fd,int error,double value){
  char buf[256];
  int rc;
  int rc2 = 0;

  //construct response
  sprintf(buf,"%d;%f;",error,value);
  rc = write(fd,buf,strlen(buf));
  if (rc != strlen(buf)){
    fprintf(stderr,"[ERR] on file writing of file descriptor %d: %s\n",fd,strerror(errno));
    rc2 = 1;
  }
  return rc2;
}

/* main function, contains the server loop */
int main(int argc,char** argv){
    struct dictionary_item* dict;
    size_t dict_count = 0;
    size_t dict_max_size;
    bool done = false;
    int fd[2] = {-1,-1};
    int rc;
    int offset = 0;

    if (argc != 3){
        fprintf(stderr,
                "[ERR] usage: %s name size\n"
                "             name -- dictionary name\n"
                "             size -- maximum dictionary size\n",
                argv[0]);
        rc = 1;
        goto err_exit;
    }

    rc = create_dict(argv[2],&dict,&dict_max_size);
    if (rc){
      goto err_exit;
    }

    rc = create_pipes(argv[1]);
    if (rc){
      goto err_dict;
    }

    do{
      struct command cmd;
      int rc2;

      fd[0] = open_pipe(argv[1],true,offset);
      if (fd[0] < 0){
        rc = 1;
        goto err_pipe;
      }

      rc = receive_command(fd[0],&cmd,&offset);
      if (rc)
          break;

      switch(cmd.op){
        case OP_ADD:
        rc2 = dict_add(dict,&dict_count,dict_max_size,cmd);
        if (rc2){
          fprintf(stderr,"[ERR] Add request received but dictionary is allready full or key allready in dictionnary.\n\n");
        }
        else{
          fprintf(stderr,"[INF] Add request received:\n Name: %s\n Value: %f\n",cmd.name,cmd.value);
        }
        break;

        case OP_REMOVE:
        rc2 = dict_remove(dict, &dict_count, cmd);
        if (rc2){
          fprintf(stderr,"[ERR] Remove request received but key not found into doctionary.\n\n");
        }
        else{
          fprintf(stderr,"[INF] Remove request received:\n Name: %s\n",cmd.name);
        }
        break;

        case OP_ASK:
        rc2 = dict_ask(dict,dict_count,&cmd);
        if (rc2){
          fprintf(stderr,"[ERR] Ask request received but key not found into dictionary.\n\n");
        }
        else{
          fprintf(stderr,"[INF] Ask request received:\n Name: %s\n Value: %f\n\n",cmd.name,cmd.value);
        }
        fd[1] = open_pipe(argv[1],false,0);
        if (fd[1] < 0){
          rc = 1;
          goto err_pipe;
        }

        rc = send_response(fd[1],rc2,cmd.value);
        close_pipe(fd[1]);
        break;

        case OP_EXIT:
        fprintf(stderr,"[INF] will quit\n");
        done = true;
        };

        if (rc) break;

        close_pipe(fd[0]);
    }
    while(!done);

    //in case of no error, not required to close the read err_pipe
    if (rc == 0){
      goto destroy_pipe;
    }

    err_pipe:
    close_pipe(fd[0]);

    destroy_pipe:
    destroy_pipes(argv[1]);

    err_dict:
    destroy_dict(dict);

    err_exit:
    return rc;
}
