#include <stdio.h>
#include "comparator.h"
#include "scanner.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: dupfinder <folder-path>\n");
        printf("Example: dupfinder .\n");
        return 1;
    }

    const char *target_dir = argv[1];
    FileList list;

    printf("Scanning folder: %s ...\n", target_dir);
    if (scan_directory(target_dir, &list) != 0) {
        return 1;
    }

    printf("Discovered %d file(s).\n\n", list.count);

    if (list.count < 2) {
        printf("Not enough files to check for duplicates.\n");
        return 0;
    }

    printf("--- Checking for Duplicates ---\n");
    int duplicates_found = 0;

    for (int i = 0; i < list.count; i++) {
        for (int j = i + 1; j < list.count; j++) {
            // First check: File sizes must match
            if (list.files[i].size == list.files[j].size) {
                // Second check: Byte-by-byte content comparison
                if (are_files_identical(list.files[i].path, list.files[j].path)) {
                    printf("\n[DUPLICATE PAIR FOUND]\n");
                    printf("  File 1: %s (%lld bytes)\n", list.files[i].path, list.files[i].size);
                    printf("  File 2: %s (%lld bytes)\n", list.files[j].path, list.files[j].size);
                    duplicates_found++;
                }
            }
        }
    }

    printf("\n-------------------------------\n");
    if (duplicates_found == 0) {
        printf("No duplicate files found in this folder.\n");
    } else {
        printf("Scan complete: %d duplicate pair(s) detected.\n", duplicates_found);
    }

    return 0;
}
