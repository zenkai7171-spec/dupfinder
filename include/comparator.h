#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <stdbool.h>

// Returns the size of a file in bytes, or -1 if the file cannot be accessed.
long long get_file_size(const char *filepath);

// Compares two files by reading their actual binary data.
// Returns true if contents are 100% identical, false otherwise.
bool are_files_identical(const char *path1, const char *path2);

#endif // COMPARATOR_H
