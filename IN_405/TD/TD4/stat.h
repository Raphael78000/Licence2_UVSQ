
#define SIZE_BUF 1024

// Print type file
// \param path    Name/path of the file
// \return        -1 on open failed, 0 on success
int print_type_file(const char *path);

// Print permission file
// \param path    Name/path of the file
// \return        -1 on open failed, 0 on success
int print_perm_file(const char *path);

// Print ID owner/ ownership file
// \param path    Name/path of the file
// \return        -1 on open failed, 0 on success
int print_ID_owner(const char *path);

// Print total size, in bytes, of file
// \param path    Name/path of the file
// \return        -1 on open failed, 0 on success
int print_size_file(const char *path);

// Print read of a directory
// \param path    Name/path of the file
// \return        -1 on open failed, 0 on success
int read_dir(const char *path);
