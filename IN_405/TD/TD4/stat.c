#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <errno.h>

#include "stat.h"

int print_type_file(const char *path){
  // test if path is null
  if (!path){
    printf("Error openning %s : %s\n",path,strerror(errno));
    return -1;
  }

  // Creat the struct stat
  struct stat stat_view;
  //Remplissage de la struct stat_view
  int success_stat=stat(path, &stat_view);

  // test stat open
  if (!success_stat){
    // File exist and haven't errors with open file.
    char type_file[SIZE_BUF];

    // Use a mask a compare with value of special type
    // Use S_IFMT for see all file type
    switch (stat_view.st_mode & S_IFMT){
      case S_IFSOCK: strcpy(type_file, "Sock       ");     break;
      case S_IFREG:  strcpy(type_file, "File       ");     break;
      case S_IFBLK:  strcpy(type_file, "Device     ");     break;
      case S_IFDIR:  strcpy(type_file, "Diry       ");     break;
      case S_IFIFO:  strcpy(type_file, "FIFO       ");     break;
      default:       strcpy(type_file, "Unknown    ");     break;
    }

    // test if file is a symlink
    lstat(path, &stat_view);
    if (S_ISLNK(stat_view.st_mode))
      strcpy(type_file, "Symlink");

      printf("Type of '%s' is: %s.\n", path, type_file);
    }

  return success_stat;
}

int print_perm_file(const char *path){
  // test if path is null
  if (!path){
    printf("Error openning %s : %s\n",path,strerror(errno));
    return -1;
  }

  // Creat the struct stat
  struct stat stat_view;
  int success_stat = stat(path,&stat_view);

  // test stat
  if (!success_stat){
    // File exist and haven't errors with open file.

    printf("User permission : ");
    (stat_view.st_mode & S_IRUSR)? printf("r"): printf("-");
    (stat_view.st_mode & S_IWUSR)? printf("w"): printf("-");
    (stat_view.st_mode & S_IXUSR)? printf("x"): printf("-");

    printf("Group permission : ");
    (stat_view.st_mode & S_IRGRP)? printf("r"): printf("-");
    (stat_view.st_mode & S_IWGRP)? printf("w"): printf("-");
    (stat_view.st_mode & S_IXGRP)? printf("x"): printf("-");

    printf("Others permission : ");
    (stat_view.st_mode & S_IROTH)? printf("r"): printf("-");
    (stat_view.st_mode & S_IWOTH)? printf("w"): printf("-");
    (stat_view.st_mode & S_IXOTH)? printf("x"): printf("-");
  }

  return success_stat;
}

int print_ID_owner(const char *path){
  // test if path is null
  if (!path){
    printf("Error openning %s : %s\n",path,strerror(errno));
    return -1;
  }

  // Creat the struct stat
  struct stat stat_view;
  int success_stat = stat(path, &stat_view);

  // test stat
  if (!success_stat) {
    // File exist and haven't errors with open file.

    printf("Ownership: UID=%ld, GID=%ld\n", (long) stat_view.st_uid, (long) stat_view.st_gid);
  }

  return success_stat;
}

int print_size_file(const char *path){
  // test if path is null
  if (!path){
    printf("Error openning %s : %s\n",path,strerror(errno));
    return -1;
  }

  // Creat the struct stat
  struct stat stat_view;
  int success_stat = stat(path, &stat_view);

  // Test stat
  if (!success_stat){
    // File exist and haven't errors with open file.

    printf("File size: %lld bytes\n", (long long) stat_view.st_size);
  }

  return success_stat;
}

int read_dir(const char *path){
  // Init directory
  DIR *dir = NULL;
  dir = opendir(path);

  // Test open directory
  if (!dir){
    printf("Error : %s reading %s\n",strerror(errno),path);
    return -1;
  }

  // Print
  printf("ls: %s\n\n", path);

  // Read in the directory
  struct dirent *_dirent = NULL;
  while ((_dirent = readdir(dir))){
    if ((strcmp(_dirent->d_name, ".") != 0) && (strcmp(_dirent->d_name, "..") != 0)) {

      // Print information of the file
      print_type_file(_dirent->d_name, 2);
      print_perm_file(_dirent->d_name, 2);
      print_ID_owner(_dirent->d_name, 2);
      print_size_file(_dirent->d_name, 2);
      printf("%s ", _dirent->d_name);
      printf("\n");
    }
  }
  printf("\n");

  // Return value of closedir
  return closedir(dir);
}
