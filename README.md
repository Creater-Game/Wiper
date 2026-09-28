Wiper - Secure File & Folder Shredder
Copyright (c) 2026 Wiper. Free to use; attribution and credit are required.

--- ABOUT ---
The ultimate digital cleanser for your files. Whether you're responsibly 
disposing of old hardware or just making sure things are gone for good, 
Wiper gets the job done. (No subscriptions required—it's just a tiny 
140KB C utility that does what it's told).

--- LEGAL DISCLAIMER & LIABILITY WAIVER ---
By downloading, compiling, installing, or interacting with Wiper in any way, 
you explicitly agree that you assume 100% of the responsibility, liability, 
and risk for any data loss, system damage, file corruption, or legal consequences 
arising from its use. 

The creator/developer of this software assumes zero liability and provides 
this tool strictly "as is" without warranty of any kind, express or implied. 
Misuse of this software to destroy critical data or hide illicit tracks is 
entirely your own responsibility. If you do not agree to these terms, 
delete this software immediately.

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
