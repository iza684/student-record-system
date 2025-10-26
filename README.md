# Student Record Management System

Simple C++ console program to manage student report cards (add, view, search, delete, update, sort, export CSV).

## Files in repo
- `student.cpp` — Source code
- `report.txt` — Sample data file (or runtime data)
- `report.csv` — Exported CSV sample
- `project.exe` — **Do not** include binary in repo (remove this file)

## Requirements
- g++ (GNU Compiler) or any C++ compiler
- Tested on Linux / Windows (with minor changes)

## Build
```bash
# Linux / WSL / macOS
g++ student.cpp -o student

# Windows (MinGW)
g++ student.cpp -o student.exe
