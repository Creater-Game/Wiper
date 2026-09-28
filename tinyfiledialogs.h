#ifndef TINYFILEDIALOGS_H
#define TINYFILEDIALOGS_H

#ifdef __c5plusplus
extern "C" {
#endif

char const * tinyfd_openFileDialog(
    char const * const aTitle,
    char const * const aDefaultPathAndFile,
    int aNumOfFilterPatterns,
    char const * const * const aFilterPatterns,
    char const * const aSingleFilterDescription,
    int aAllowMultipleSelects);

char const * tinyfd_selectFolderDialog(
    char const * const aTitle,
    char const * const aDefaultPath);

int tinyfd_messageBox(
    char const * const aTitle,
    char const * const aMessage,
    char const * const aDialogType,
    char const * const aIconType,
    int aDefaultButton);

#ifdef __cplusplus
}
#endif

#endif