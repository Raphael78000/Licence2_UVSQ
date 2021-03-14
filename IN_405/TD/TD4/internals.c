#include "internals.h"

int capture_file(const char* path, struct file* parent){
	struct stat stat_view;
	int check;

	check = lstat(path, &stat_view);
	if (check){
		printf("erro %s in capture_file\n",strerror(errno));
		return 1;
	}

	if (!path){
		printf("error %s : %s is invalid\n",strerror(errno),path);
		return 1;
	}
	
	if (S_ISDIR(stat_view.st_mode) || S_ISREG(stat_view.st_mode) || S_ISLNK(stat_view.st_mode)){

		if		(S_ISLNK(stat_view.st_mode))		parent->type = FT_LINK;
		else if (S_ISREG(stat_view.st_mode))		parent->type = FT_REGULAR;
		else if (S_ISDIR(stat_view.st_mode))		parent->type = FT_DIRECTORY;
		else printf("error : type of file isn't listed in the options\n");

		parent->mode = stat_view.st_mode;                                            
	
		parent->user_id = stat_view.st_uid;                                           

		strcpy(parent->name,1 + strrchr(path,'/'));                             

		parent->next = NULL;

		if 		(parent->type == FT_LINK)		readlink(path,parent->attribute.target,NAME_MAX);
		else if (parent->type == FT_REGULAR)	parent->attribute.size = stat_view.st_size;
		else if (parent->type == FT_DIRECTORY)	parent->attribute.child = NULL;
	}
	
	return 0;
}

int browse_directory(const char *path, struct file **current){
	DIR* dirp;
	struct dirent* dir;
	int check;
	struct file* fichier;
	
	fichier = malloc(sizeof(struct file));
	*current = fichier;

	dirp = opendir(path); 
	if (!dirp){
		printf("error %s : %s did not open correctly\n",strerror(errno),path);
		return 1;
	}
	while ((dir = readdir(dirp)) != NULL){
		
		if ((strcmp(dir->d_name,".") != 0) && (strcmp(dir->d_name,"..") != 0)){
			
			char* name = malloc(sizeof(char)*NAME_MAX);
			strcpy(name,path); strcat(name,"/"); strcat(name,dir->d_name);
			capture_file(name,(fichier));
			
			if (dir->d_type == DT_DIR){
				//((fichier)->attribute.child) = malloc(sizeof(struct file));
				browse_directory(name,&((fichier)->attribute.child));
			}
			free(name);
			(fichier->next) = malloc(sizeof(struct file));
			(fichier) = ((fichier)->next);
		}
	}
	fichier = NULL;
	
	check = closedir(dirp);
	if (check){
		printf("error %s closing directory\n",strerror(errno));
		return 1;
	}

	return 0;
}

int create_regular(const char *path, const struct file *regular){
	struct stat stat_view;
	int check, desc;
	char nom[NAME_MAX];
	char ecri = 'a';

	check = lstat(path, &stat_view);
	if (check){
		printf("error %s in create_regular\n",strerror(errno));
		return 1;
	}

	if (regular->type != FT_REGULAR){
		printf("file is not regular\n");
		return 1;
	}

	strcpy(nom,path); strcat(nom,"/"); strcat(nom,regular->name);

	//création du fichier et écriture de file->name
	desc = open(nom,O_CREAT | O_WRONLY);
	if (desc == -1){
		printf("error %s in create_regular\n",strerror(errno));
		return 1;
	}
	//écriture de file->attribute.size
	for (int i = 0;i < (regular->attribute.size);i++){
		check = write(desc,&ecri,sizeof(char));
		if (check == -1){
			printf("erreur write function in create_regular\n");
			return 1;
		}
	}
	//changement file->mode
	chmod(nom,regular->mode);
	
	//chnagement file->user_id
	chown(nom,regular->user_id,000);
	
	check = close(desc);
	if (check){
		printf("error %s : in create_regular\n",strerror(errno));
		return 1;
	}
	
	return 0;
}

