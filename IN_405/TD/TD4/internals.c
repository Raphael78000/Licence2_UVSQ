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
                                                                                //Remplissage de parent->type
  if (S_ISLNK(stat_view.st_mode))      parent->type = FT_LINK;
  else if (S_ISREG(stat_view.st_mode)) parent->type = FT_REGULAR;
  else if (S_ISDIR(stat_view.st_mode)) parent->type = FT_DIRECTORY;
  else printf("error : type of file isn't listed in the options\n");

  parent->mode = stat_view.st_mode;                                             //Remplissage de parent->mode

  parent->user_id = stat_view.st_uid;                                           //Remplissage de parent->user_id

  strcpy(parent->name,strrchr(path,'/'));                                       //Remplissage de parent->name

  parent->next = NULL;                                                          //Initialisation de paren->next à zéro

                                                                                //Remplissage parent->attribute
  if (parent->type == FT_LINK){ readlink(path,parent->attribute.target,NAME_MAX); printf("parent->attribute.target: %s\n",parent->attribute.target);}
  else if (parent->type == FT_REGULAR){  parent->attribute.size = stat_view.st_size; printf("parent->attribute.size: %lu\n",parent->attribute.size);}
  else if (parent->type == FT_DIRECTORY) parent->attribute.child = NULL;

  return 0;
}

int browse_directory(const char *path, struct file **current){
  DIR *dirp;
  struct dirent *dp;
	struct stat s;
	char *name;

  //Affichage du contenu du repertoire
  while( (dp = readdir(dirp)) != NULL){
    if((strcmp(dp->d_name,".") != 0) && (strcmp(dp->d_name,"..") != 0)){
			while ((*current)->next != NULL){
				current = &((*current)->next);
			}
			strcat(name,path); strcat(name,"/"); strcat(name,dp->d_name);
			capture_file(name,*current);

			//dans le cas où il s'agit d'un répertoire
			if((strcmp(dp->d_name,".") != 0) && (strcmp(dp->d_name,"..") != 0) &&(S_ISDIR(s.st_mode))){
				strcat(name,"/"); strcat(name,dp->d_name);
	      return browse_directory(name,&((*current)->attribute.child));
			}
		}
	}
	closedir(dirp);
}
