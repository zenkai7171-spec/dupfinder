#ifndef SCANNER_H
#define SCANNER_H

#define MAX_FILES 1024
#define MAX_PATH_LEN 512

typedef struct {
    char path[MAX_PATH_LEN];
    long long size;
} FileEntry;

typedef struct {
    FileEntry files[MAX_FILES];
    int count;
} FileList;

// Scans target directory and populates list with regular files
int scan_directory(const char *dir_path, FileList *list);

#endif // SCANNER_H
