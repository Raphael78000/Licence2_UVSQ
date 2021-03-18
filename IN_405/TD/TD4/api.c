#include "api.h"

int capture_tree(const char *path, struct file **phantom){
	int check;

	check = browse_directory(path,phantom);
	if (check){
		printf("error in browse_directory function\n");
		return 1;
	}
	
	return 0;
}

int create_phantom(const char *path, struct file *phantom){
	struct file* create;
	int check;
	
	create = phantom;
	
	while (create != NULL){
		if (create->type == FT_REGULAR){
			check = create_regular(path,create);
			if (check){
				printf("error with create_regular function in create_phantom\n");
				return 1;
			}
		}
		else if (create->type == FT_DIRECTORY){
			check = create_directory(path,create);
			if (check){
				printf("error with create_directory function in create_phantom\n");
				return 1;
			}
			
			char nom[NAME_MAX]; strcpy(nom,path); strcat(nom,"/"); strcat(nom,create->name);
			create_phantom(nom,create->attribute.child);
		}
		else if (create->type == FT_LINK){
			check = create_link(path,create);
			if (check){
				printf("error with create_link function in create_phantom\n");							
				return 1;
			}
		}
		create = create->next;
	}
	
	return 0;
}

void free_structfile(struct file* phantom){
	struct file* origin;
	
	origin = phantom;
	
	while (origin != NULL){
		if ((origin->type == FT_REGULAR) || (origin->type == FT_LINK)) free(origin);
		
		else if (origin->type == FT_DIRECTORY) free_structfile(origin->attribute.child);
		
		origin = origin->next;
	}
}
