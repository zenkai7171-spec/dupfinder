#include "scanner.h"
#include "comparator.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int scan_directory(const char *dir_path, FileList *list) {
    list->count = 0;

    DIR *dir = opendir(dir_path);
    if (!dir) {
        printf("Error: Could not open directory '%s'\n", dir_path);
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip current (.) and parent (..) directory links
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[MAX_PATH_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISREG(st.st_mode)) { // Only regular files, skip subfolders
                if (list->count < MAX_FILES) {
                    strncpy(list->files[list->count].path, full_path, MAX_PATH_LEN - 1);
                    list->files[list->count].path[MAX_PATH_LEN - 1] = '\0';
                    list->files[list->count].size = (long long)st.st_size;
                    list->count++;
                } else {
                    printf("Warning: Hit maximum file capacity (%d).\n", MAX_FILES);
                    break;
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
