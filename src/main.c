#include <stdio.h>
#include <stdbool.h>
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

    // Array to track if a file was deleted during this run
    bool deleted[MAX_FILES] = { false };
    int duplicates_found = 0;
    long long total_bytes_freed = 0;

    printf("=== Starting Interactive Duplicate Analysis ===\n\n");

    for (int i = 0; i < list.count; i++) {
        if (deleted[i]) continue;

        for (int j = i + 1; j < list.count; j++) {
            if (deleted[j]) continue;

            // Size check first
            if (list.files[i].size == list.files[j].size) {
                // Byte-by-byte comparison
                if (are_files_identical(list.files[i].path, list.files[j].path)) {
                    duplicates_found++;
                    printf("----------------------------------------\n");
                    printf("[DUPLICATE FOUND]\n");
                    printf("  [1] %s (%lld bytes)\n", list.files[i].path, list.files[i].size);
                    printf("  [2] %s (%lld bytes)\n", list.files[j].path, list.files[j].size);
                    printf("Actions:\n");
                    printf("  1. Delete [2] (Keep [1])\n");
                    printf("  2. Delete [1] (Keep [2])\n");
                    printf("  3. Skip (Keep both)\n");
                    printf("Enter choice (1-3): ");

                    int choice = 0;
                    if (scanf("%d", &choice) != 1) {
                        // Clear invalid input buffer
                        while (getchar() != '\n');
                        choice = 3;
                    }

                    if (choice == 1) {
                        if (remove(list.files[j].path) == 0) {
                            printf("-> Deleted: %s\n", list.files[j].path);
                            deleted[j] = true;
                            total_bytes_freed += list.files[j].size;
                        } else {
                            printf("-> Error: Failed to delete %s\n", list.files[j].path);
                        }
                    } else if (choice == 2) {
                        if (remove(list.files[i].path) == 0) {
                            printf("-> Deleted: %s\n", list.files[i].path);
                            deleted[i] = true;
                            total_bytes_freed += list.files[i].size;
                            break; // File i is gone, stop comparing it against others
                        } else {
                            printf("-> Error: Failed to delete %s\n", list.files[i].path);
                        }
                    } else {
                        printf("-> Skipped.\n");
                    }
                    printf("\n");
                }
            }
        }
    }

    printf("========================================\n");
    printf("Scan Summary:\n");
    printf("  Duplicate pairs detected : %d\n", duplicates_found);
    printf("  Total disk space freed   : %lld bytes (%.2f KB)\n", 
           total_bytes_freed, total_bytes_freed / 1024.0);
    printf("========================================\n");

    return 0;
}
