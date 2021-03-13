#include "internals.h"

int capture_file(const char* path, struct file* parent){
  struct stat stat_view;
  struct passwd *pwd;
  lstat(path, &stat_view);
                                                                                //Vérification que le chemin entré par l'utilisateur existe bien
  if (!path){
    printf("error %s : %s is invalid\n",strerror(errno),path);
    return 1;
  }

  parent = malloc(sizeof(struct file));
                                                                                //Remplissage de parent->type
  if      (S_ISLNK(stat_view.st_mode))      parent->type = FT_LINK;
  else if (S_ISREG(stat_view.st_mode))      parent->type = FT_REGULAR;
  else if (S_ISDIR(stat_view.st_mode))      parent->type = FT_DIRECTORY;
  else printf("error : type of file isn't listed in the options\n");

  parent->mode = stat_view.st_mode;                                             //Remplissage de parent->mode

  parent->user_id = stat_view.st_uid;                                             //Remplissage de parent->user_id

  strcpy(parent->name,1 + strrchr(path,'/'));                                   //Remplissage de parent->name

  parent->next = malloc(sizeof(struct file));
                                                                                //Remplissage parent->attribute
  if      (parent->type == FT_LINK)      readlink(path,parent->attribute.target,NAME_MAX);
  else if (parent->type == FT_REGULAR)   parent->attribute.size = stat_view.st_size;
  else if (parent->type == FT_DIRECTORY) parent->attribute.child = NULL;
  printf("parent->name %s\n\n",parent->name);

  return 0;
}

int browse_directory(const char *path, struct file **current){
  DIR* dirp;
  struct dirent* dir;
  char* name;
  int check;

  dirp = opendir(path);
  if (!dirp){
    printf("error %s: %s did not open correctly\n",strerror(errno),path);
    return 1;
  }

  while (dir = readdir(dirp)){
    if ((strcmp(dir->d_name,".") != 0) && (strcmp(dir->d_name,"..") != 0)){
      strcat(name,path); strcat(name,"/"); strcat(name,dir->d_name);

      check = capture_file(name,*current);
      if (check){
        printf("error concerning the capture_file function\n");
        return 1;
      }

      if ((*current)->type == FT_DIRECTORY){
        browse_directory(name,&((*current)->attribute.child));
      }
      (*current) = ((*current)->next);
    }
  }
  check = closedir(dirp);
  if (check){
    printf("error concerning closing process\n");
    return 1;
  }

  return 0;
}
