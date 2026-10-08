#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "scanner.h"

// Helper function to recursively collect files
static void scan_recursive(const char *dir_path, FileList *list) {
    DIR *d = opendir(dir_path);
    if (!d) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        // Skip current and parent directory pointers
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build full path
        char full_path[MAX_PATH_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) != 0) {
            continue;
        }

        // If it is a directory, recurse into it
        if (S_ISDIR(st.st_mode)) {
            scan_recursive(full_path, list);
        }
        // If it is a regular file, record it
        else if (S_ISREG(st.st_mode)) {
            if (list->count < MAX_FILES) {
                strncpy(list->files[list->count].path, full_path, MAX_PATH_LEN - 1);
                list->files[list->count].path[MAX_PATH_LEN - 1] = '\0';
                list->files[list->count].size = st.st_size;
                list->count++;
            }
        }
    }

    closedir(d);
}

int scan_directory(const char *dir_path, FileList *list) {
    list->count = 0;
    
    // Check if base directory exists
    DIR *test = opendir(dir_path);
    if (!test) {
        return 0;
    }
    closedir(test);

    scan_recursive(dir_path, list);
    return 1;
}
