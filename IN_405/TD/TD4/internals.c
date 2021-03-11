#include "internals.h"

int capture_file(const char *path, struct file *parent){
  struct stat stat_view;
  struct passwd *pwd;
  lstat(path, &stat_view);

  //Remplissage de parent->type
  if (S_ISLNK(stat_view.st_mode))      parent->type = FT_LINK;
  else if (S_ISREG(stat_view.st_mode)) parent->type = FT_REGULAR;
  else if (S_ISDIR(stat_view.st_mode)) parent ->type = FT_DIRECTORY;
  else printf("error : type of file isn't listed in the options\n");
printf("-\n");
  //Remplissage de parent->mode
  //parent->mode = stat_view.st_mode;

  //Remplissage de parent->user_id
  parent->user_id = stat_view.st_uid;

  //Remplissage de parent->name
  strcpy(parent->name,strrchr(path,'/'));

  //Initialisation de paren->next à zéro
  parent->next = NULL;

  //Remplissage parent->attribute
  if (parent->type == FT_LINK) readlink(path,parent->attribute.target,NAME_MAX);
  else if (parent->type == FT_REGULAR)  parent->attribute.size = stat_view.st_size;
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

void print_file(const struct file* panther){
	fprintf(stdout, "\n\nThe name of the file is %s\n"
					"It is owned by %u\n"
					"Its access is defined by %u\n"
					"It is a ",
					panther->name, panther->user_id, panther->mode);


	switch ( panther->type )
	{
		case FT_REGULAR : fprintf(stdout, "regular file\nIts size is %lu\n", panther->attribute.size);
						  break;
		case FT_DIRECTORY : fprintf(stdout, "directory\nHere is what is inside :\n");
							struct file* fox = panther->attribute.child;
							while ( fox )
							{
								print_file(fox);
								fox = fox->next;
							}
						    break;
		case FT_LINK : fprintf(stdout, "symbolic link\nThe name of its target is %s\n", panther->attribute.target);
					   break;
		default : fprintf(stdout, "not a regular file, a directory or a symbolic link\n");
			      break;
	}
}
