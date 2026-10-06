# dupfinder 🔍

A fast, lightweight CLI utility written in pure C to detect and safely clean duplicate files based on content, not filenames.

## The Problem
Downloads and game folders often accumulate duplicate files with completely different names (e.g., `setup.exe` and `setup(1).exe`), wasting gigabytes of disk space.

## How It Works
Instead of reading every file entirely, `dupfinder` uses a 3-tier check:
1. **Size check:** Skips files with mismatched byte lengths immediately.
2. **Chunk check:** Compares the initial 1 KB buffer.
3. **Byte check:** Compares remaining contents in 4 KB streams to preserve memory.

## Roadmap
- [x] Repository setup & architecture
- [ ] Milestone 1: Two-file binary comparison engine
- [ ] Milestone 2: Folder scanner (`<dirent.h>`)
- [ ] Milestone 3: Interactive deletion CLI with storage savings counter
- [ ] Milestone 4: Subdirectory recursion (optional stretch goal)

## Build Instructions
```bash
gcc -Iinclude src/main.c src/comparator.c src/scanner.c -o dupfinder
./dupfinder <folder-path>
