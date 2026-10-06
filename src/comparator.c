#include "comparator.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define CHUNK_SIZE 4096 // 4 KB buffer

long long get_file_size(const char *filepath) {
    struct stat st;
    if (stat(filepath, &st) == 0) {
        return (long long)st.st_size;
    }
    return -1;
}

bool are_files_identical(const char *path1, const char *path2) {
    long long size1 = get_file_size(path1);
    long long size2 = get_file_size(path2);

    // Fast check: if sizes don't match or a file is missing, they aren't duplicates
    if (size1 < 0 || size2 < 0 || size1 != size2) {
        return false;
    }

    FILE *f1 = fopen(path1, "rb");
    FILE *f2 = fopen(path2, "rb");

    if (!f1 || !f2) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return false;
    }

    unsigned char buf1[CHUNK_SIZE];
    unsigned char buf2[CHUNK_SIZE];
    size_t bytes1, bytes2;
    bool identical = true;

    // Stream both files in 4 KB chunks
    while (1) {
        bytes1 = fread(buf1, 1, CHUNK_SIZE, f1);
        bytes2 = fread(buf2, 1, CHUNK_SIZE, f2);

        if (bytes1 != bytes2) {
            identical = false;
            break;
        }

        if (bytes1 == 0) {
            break; // Reached End-Of-File (EOF) with all bytes matching
        }

        if (memcmp(buf1, buf2, bytes1) != 0) {
            identical = false;
            break;
        }
    }

    fclose(f1);
    fclose(f2);
    return identical;
}
