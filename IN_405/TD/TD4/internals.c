#include "internals.h"

struct file* organize_struct(struct file* organize){

	if (organize->user_id != 0){
		organize->next = organize_struct(organize->next);
		return organize;
	}
	else{
		free(organize);
		return NULL;
	}
}

int capture_file(const char* path, struct file* parent){
	struct stat stat_view;
	int check;

	check = lstat(path, &stat_view);
	if (check == -1){
		printf("erro %s in capture_file\n",strerror(errno));
		return 1;
	}

	if (!path){
		printf("error %s : %s is invalid\n",strerror(errno),path);
		return 1;
	}
	
	if (S_ISDIR(stat_view.st_mode) || S_ISREG(stat_view.st_mode) || S_ISLNK(stat_view.st_mode)){

		//Remplissage du champ "file type" de la struct file 
		if		(S_ISLNK(stat_view.st_mode))		parent->type = FT_LINK;
		else if (S_ISREG(stat_view.st_mode))		parent->type = FT_REGULAR;
		else if (S_ISDIR(stat_view.st_mode))		parent->type = FT_DIRECTORY;

		//Remplissage du champ "file access" de la struct file 
		parent->mode = stat_view.st_mode;                                            
		
		//Remplissage du champ "ID file owner" de la struct file 
		parent->user_id = stat_view.st_uid;                                           

		//Remplissage du champ "file name" de la struct file 
		strcpy(parent->name,1 + strrchr(path,'/'));                             
		
		//Initialisation "next element" à NULL
		parent->next = NULL;

		//Remplissage du champ "attribute" de la struct file en fonction du "file type"
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
		
		//Afin de ne pas avoir dle nom du répertoire en cours ni celui au dessus  
		if ((strcmp(dir->d_name,".") != 0) && (strcmp(dir->d_name,"..") != 0)){
			
			char name[NAME_MAX];
			strcpy(name,path); strcat(name,"/"); strcat(name,dir->d_name);				//Ajout du nom du fichier, lien symbolique ou répertoire au path
 
			check = capture_file(name,fichier);
			if (check){
				printf("error with capture_file function in browse_directory\n");
				return 1;
			}
			
			if (dir->d_type == DT_DIR){
				browse_directory(name,&(fichier->attribute.child));
			}
			fichier->next = malloc(sizeof(struct file));
			fichier = fichier->next;
		}
	}
	
	*current = organize_struct(*current);												//Suppression du dernier élèment de chaque liste chaînée (voir README.md	
	
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
	char ecri = 'a';													//un char fait un octet

	check = lstat(path, &stat_view);
	if (check == -1){
		printf("error %s in create_regular\n",strerror(errno));
		return 1;
	}

	if (regular->type != FT_REGULAR){
		printf("file is not regular in create_regular\n");
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
	check = chmod(nom,regular->mode);
	if (check == -1){
		printf("error %s : in create_regular\n",strerror(errno));
		return 1;
	}
	
	//changement file->user_id
	check = chown(nom,regular->user_id,-1);								//Le choix du -1 s'explique par ce nombre ne change pas les permissions de groupe_id
	if (check == -1){
		printf("error %s : in create_regular\n",strerror(errno));
		return 1;
	}
	
	check = close(desc);
	if (check == -1){
		printf("error %s : in create_regular\n",strerror(errno));
		return 1;
	}
	
	return 0;
}

int create_directory(const char *path, const struct file *directory){
	struct stat stat_view;
	int check,desc;
	char nom[NAME_MAX];
	
	check = lstat(path, &stat_view);
	if (check == -1){
		printf("error %s in create_directory\n",strerror(errno));
		return 1;
	}

	if (directory->type != FT_DIRECTORY){
		printf("file is not directory in create_directory\n");
		return 1;
	}

	strcpy(nom,path); strcat(nom,"/"); strcat(nom,directory->name);

	//création répertoire avec directory->mode et directory->name
	desc = mkdir(nom,directory->mode);
	if (desc == -1){
		printf("error %s in create_directory\n",strerror(errno));
		return 1;
	}

	//changement file->user_id
	check = chown(nom,directory->user_id,-1);							//Le choix du -1 s'explique par ce nombre ne change pas les permissions de groupe_id
	if (check == -1){
		printf("error %s : in create_directory\n",strerror(errno));
		return 1;
	}

	return 0;
}

int create_link(const char *path, const struct file *link){
	struct stat stat_view;
	int check,desc;
	char nom[NAME_MAX];
	
	check = lstat(path, &stat_view);
	if (check == -1){
		printf("error %s in create_link\n",strerror(errno));
		return 1;
	}

	if (link->type != FT_LINK){
		printf("file is not link in create_link\n");
		return 1;
	}
	
	strcpy(nom,path); strcat(nom,"/"); strcat(nom,link->name);
	
	//création du lien symbolique avec sa cible
	desc = symlink(link->attribute.target,nom);
	if (desc == -1){
		printf("error %s in create_link\n",strerror(errno));
		return 1;
	}

	/* Dans la création d'un lien symbolique on ne peut pas en modifier les permissions d'accès
	 * car le lien symbolique hérite des droits du fichier sur lequel il pointe.
	 */
	
	//changement file->user_id
	check = lchown(nom,link->user_id,-1);								//Le choix du -1 s'explique par ce nombre ne change pas les permissions de groupe_id
	if (check == -1){
		printf("error %s : in create_link\n",strerror(errno));
		return 1;
	}
	
	return 0;
}

