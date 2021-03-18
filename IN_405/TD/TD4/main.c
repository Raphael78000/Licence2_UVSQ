#include "api.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

void show_file(const struct file* fichier){
	const struct file* navig;
	
	navig = fichier;
	
	if (!navig){
		printf("error %s in show_file\n",strerror(errno));
		return;
	}
	
	while (navig != NULL){
	printf("navig->name = %s\n",navig->name);
	printf("navig->mode = %u\n",navig->mode);
	printf("navig->user_id = %u\n",navig->user_id);
	
	if (navig->type == FT_LINK) printf("navig->attribute.target = %s\n",navig->attribute.target);
	
	if (navig->type == FT_DIRECTORY){
		printf("	file in %s:\n",navig->name);
		struct file* spdirect; spdirect = navig->attribute.child;
		show_file(spdirect);
		printf("end of %s directory\n",navig->name);
		}
	navig = navig->next;
	}
}

int main(int argc, char **argv){
	struct file** origin = malloc(sizeof(struct file*));
	int check;

	if (argc != 3){
		printf("Bad usage: %s src dest\n"
			"   - src : source directory\n"
			"   - dest: phantom directory\n", argv[0]);
		return EXIT_FAILURE;
	}

	//remplissage de la struct origin à partir du path souhaité
	check = capture_tree(argv[1],origin);
	if (check){
		printf("error with capture_tree function in main\n");
		return 1;
	}
	
	//création du répertoire phantom
	check = create_phantom(argv[2],*origin);
	if (check){
		printf("error with create_phantom function in main\n");
		return 1;
	}
	
	free(origin);
	
	return 0;
}
