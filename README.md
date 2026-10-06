# dupfinder

A fast, lightweight command-line duplicate file finder and cleaner written in pure C. 

Instead of relying on file names, `dupfinder` inspects binary content using multi-tier checks to identify identical files and clean up storage interactively.

---

## Features

- **Binary-Level Content Verification**: Accurately detects duplicates even if files have different names or extensions.
- **2-Tier Fast Comparison Engine**:
  1. **File Size Check**: Immediately discards non-matching file pairs using `stat()`.
  2. **Buffered Chunk Comparison**: Reads matching-size files in 4 KB chunks via `fread()` and `memcmp()` to keep RAM footprint low.
- **Directory Traversal**: Automatically scans folders using standard `<dirent.h>`.
- **Interactive Deletion Prompt**: Choose which file copy to keep or delete directly from the terminal.
- **Disk Space Metrics**: Displays real-time calculations of reclaimed storage in bytes and KB.
- **Zero External Dependencies**: Built strictly using standard C libraries (`stdio.h`, `string.h`, `dirent.h`, `sys/stat.h`).

---

## Project Structure

```text
dupfinder/
├── include/
│   ├── comparator.h    # Prototypes for size and byte comparison
│   └── scanner.h       # Directory scanning structures & prototypes
├── src/
│   ├── comparator.c    # File I/O and buffered byte comparison logic
│   ├── scanner.c       # Directory reading and file aggregation
│   └── main.c          # CLI entry point, user prompt, and file removal
└── README.md
