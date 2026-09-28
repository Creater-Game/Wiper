Wiper - Secure File & Folder Shredder
Copyright (c) 2026 Wiper. Free to use; attribution and credit are required.

--- HOW TO COMPILE & RUN ---

1. WINDOWS:
   Make sure you have GCC (like MinGW) installed, then run:
   gcc wiper.c tinyfiledialogs.c -o Wiper.exe -lcomdlg32 -lole32 -lshell32

2. LINUX:
   Open your terminal in this folder and run:
   gcc wiper.c tinyfiledialogs.c -o wiper -pthread -ldl

3. macOS:
   Open your terminal in this folder and run:
   clang wiper.c tinyfiledialogs.c -o wiper -framework Cocoa
