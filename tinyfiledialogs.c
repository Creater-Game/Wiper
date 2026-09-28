#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tinyfiledialogs.h"

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>

char const * tinyfd_openFileDialog(
    char const * const aTitle,
    char const * const aDefaultPathAndFile,
    int aNumOfFilterPatterns,
    char const * const * const aFilterPatterns,
    char const * const aSingleFilterDescription,
    int aAllowMultipleSelects) {
    
    static char filename[MAX_PATH];
    ZeroMemory(filename, sizeof(filename));
    if (aDefaultPathAndFile) strncpy(filename, aDefaultPathAndFile, MAX_PATH - 1);

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        return filename;
    }
    return NULL;
}

char const * tinyfd_selectFolderDialog(
    char const * const aTitle,
    char const * const aDefaultPath) {
    
    static char folderPath[MAX_PATH];
    ZeroMemory(folderPath, sizeof(folderPath));

    BROWSEINFOA bi = { 0 };
    bi.lpszTitle = aTitle;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (pidl != 0) {
        SHGetPathFromIDListA(pidl, folderPath);
        CoTaskMemFree(pidl);
        return folderPath;
    }
    return NULL;
}

int tinyfd_messageBox(
    char const * const aTitle,
    char const * const aMessage,
    char const * const aDialogType,
    char const * const aIconType,
    int aDefaultButton) {
    
    UINT flags = 0;
    if (strcmp(aDialogType, "yesno") == 0) flags |= MB_YESNO;
    else flags |= MB_OK;

    if (strcmp(aIconType, "warning") == 0) flags |= MB_ICONWARNING;
    else if (strcmp(aIconType, "error") == 0) flags |= MB_ICONERROR;
    else if (strcmp(aIconType, "question") == 0) flags |= MB_ICONQUESTION;
    else flags |= MB_ICONINFORMATION;

    if (aDefaultButton == 0) flags |= MB_DEFBUTTON2;

    int response = MessageBoxA(NULL, aMessage, aTitle, flags);
    if (response == IDYES || response == IDOK) return 1;
    return 0;
}

#else
// Linux / macOS fallback using standard console prompts if GUI toolkits aren't bound
char const * tinyfd_openFileDialog(char const * const t, char const * const d, int n, char const * const * f, char const * const s, int m) {
    static char path[1024];
    printf("Enter file path to wipe: ");
    if (fgets(path, sizeof(path), stdin)) {
        path[strcspn(path, "\n")] = 0;
        return path;
    }
    return NULL;
}
char const * tinyfd_selectFolderDialog(char const * const t, char const * const d) {
    static char path[1024];
    printf("Enter folder path to wipe: ");
    if (fgets(path, sizeof(path), stdin)) {
        path[strcspn(path, "\n")] = 0;
        return path;
    }
    return NULL;
}
int tinyfd_messageBox(char const * const t, char const * const m, char const * const d, char const * const i, int b) {
    printf("[%s] %s\n", t, m);
    return 1;
}
#endif