#include "internals.h"

int capture_file(const char* path, struct file* parent){
	struct stat stat_view;
	struct passwd *pwd;
	lstat(path, &stat_view);

	if (!path){
		printf("error %s : %s is invalid\n",strerror(errno),path);
		return 1;
	}

	if		(S_ISLNK(stat_view.st_mode))		parent->type = FT_LINK;
	else if (S_ISREG(stat_view.st_mode))		parent->type = FT_REGULAR;
	else if (S_ISDIR(stat_view.st_mode))		parent->type = FT_DIRECTORY;
	else printf("error : type of file isn't listed in the options\n");

	parent->mode = stat_view.st_mode;                                            

	parent->user_id = stat_view.st_uid;                                           

	strcpy(parent->name,1 + strrchr(path,'/')); printf("%s\n",parent->name);                               

	parent->next = NULL;

	if 		(parent->type == FT_LINK)		readlink(path,parent->attribute.target,NAME_MAX);
	else if (parent->type == FT_REGULAR)	parent->attribute.size = stat_view.st_size;
	else if (parent->type == FT_DIRECTORY)	parent->attribute.child = NULL;

	return 0;
}

int browse_directory(const char *path, struct file **current){
	DIR* dirp;
	struct dirent* dir;
	int check;

	dirp = opendir(path); 
	if (!dirp){
		printf("error %s : %s did not open correctly\n",strerror(errno),path);
		return 1;
	}
	while ((dir = readdir(dirp)) != NULL){
		
		if ((strcmp(dir->d_name,".") != 0) && (strcmp(dir->d_name,"..") != 0)){
			
			char* name = malloc(sizeof(char)*NAME_MAX);
			strcpy(name,path); strcat(name,"/"); strcat(name,dir->d_name);
			capture_file(name,(*current));
			
			if (dir->d_type == DT_DIR){
				((*current)->attribute.child) = malloc(sizeof(struct file));
				browse_directory(name,&((*current)->attribute.child));
			}
			free(name);
		}
		(*current) = ((*current)->next);
		(*current) = malloc(sizeof(struct file));
		
	}
	check = closedir(dirp);
	if (check){
		printf("error %s closing directory\n",strerror(errno));
		return 1;
	}

	return 0;
}
