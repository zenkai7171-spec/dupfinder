#include <stdio.h>
#include "comparator.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    printf("Checking:\n  [1] %s\n  [2] %s\n", argv[1], argv[2]);

    if (are_files_identical(argv[1], argv[2])) {
        printf("=> MATCH: Files are 100%% identical duplicates!\n");
    } else {
        printf("=> NO MATCH: Files are different.\n");
    }

    return 0;
}
