#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "tinyfiledialogs.h"

#define BUFFER_SIZE 4096

// Check if path is a critical system directory
int is_critical_path(const char *path) {
    char lower_path[1024];
    strncpy(lower_path, path, sizeof(lower_path) - 1);
    
    for(int i = 0; lower_path[i]; i++){
        if(lower_path[i] >= 'A' && lower_path[i] <= 'Z')
            lower_path[i] += 32;
    }

    if (strstr(lower_path, "windows") || 
        strstr(lower_path, "system32") || 
        strstr(lower_path, "program files") ||
        strcmp(path, "/") == 0 || 
        strcmp(path, "/bin") == 0 || 
        strcmp(path, "/etc") == 0) {
        return 1;
    }
    return 0;
}

// Securely overwrite and delete a single file
int wipe_file(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) return -1;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    if (file_size <= 0) {
        remove(filepath);
        return 0;
    }

    file = fopen(filepath, "wb");
    if (!file) return -1;

    srand((unsigned int)time(NULL));
    long bytes_written = 0;
    char buffer[BUFFER_SIZE];

    while (bytes_written < file_size) {
        long chunk = (file_size - bytes_written < BUFFER_SIZE) ? 
                     (file_size - bytes_written) : BUFFER_SIZE;

        for (int i = 0; i < chunk; i++) {
            buffer[i] = (char)(rand() % 256);
        }

        fwrite(buffer, 1, chunk, file);
        bytes_written += chunk;
    }

    fflush(file);
    fclose(file);
    return remove(filepath);
}

// Recursive directory wiper
int wipe_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return -1;

    struct dirent *entry;
    char fullpath[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                wipe_directory(fullpath);
                rmdir(fullpath);
            } else {
                printf("[WIPING] %s\n", fullpath);
                wipe_file(fullpath);
            }
        }
    }
    closedir(dir);
    return rmdir(path);
}

int main() {
    // 1. Legal Disclaimer & Copyright Notice
    int disclaimer = tinyfd_messageBox(
        "Wiper.exe - Legal Notice & Disclaimer",
        "WARNING: Wiper is a destructive tool that permanently destroys data.\n\n"
        "Any damage, data loss, or system instability caused by this software is entirely your responsibility.\n\n"
        "Copyright (c) 2026 Wiper. Free to use; attribution and credit are required.\n\n"
        "Do you accept these terms and wish to launch Wiper?",
        "yesno",
        "warning",
        0
    );

    if (disclaimer == 0) {
        return 0;
    }

    // 2. Select Mode (File or Folder)
    int choice = tinyfd_messageBox(
        "Wiper - Select Mode",
        "Click [Yes] to wipe a single File, or [No] to wipe an entire Folder.",
        "yesno",
        "question",
        1
    );

    const char *target = NULL;
    if (choice == 1) {
        target = tinyfd_openFileDialog("Select File to Destroy", "", 0, NULL, NULL, 0);
    } else {
        target = tinyfd_selectFolderDialog("Select Folder to Destroy", "");
    }

    if (!target) {
        return 0;
    }

    // 3. System-Critical Safety Check
    if (is_critical_path(target)) {
        int safety_override = tinyfd_messageBox(
            "CRITICAL SYSTEM WARNING!",
            "WARNING: The target you selected appears to be a vital system path!\n"
            "Wiping this will brick or destroy your operating system.\n\n"
            "Are you absolutely SURE you want to continue?",
            "yesno",
            "error",
            0
        );

        if (safety_override == 0) {
            tinyfd_messageBox("Aborted", "Operation cancelled safely. System files protected.", "ok", "info", 1);
            return 0;
        }
    }

    printf("\n[*] Target acquired: %s\n", target);
    printf("[*] Overwriting and destroying data...\n");

    struct stat st;
    int result = -1;

    if (stat(target, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            result = wipe_directory(target);
        } else {
            result = wipe_file(target);
        }
    }

    // 4. Success Popup
    if (result == 0) {
        tinyfd_messageBox("Done!", "Target successfully overwritten with nonsense and destroyed!\n\n(Powered by Wiper)", "ok", "info", 1);
    } else {
        tinyfd_messageBox("Error", "An error occurred while wiping the target.", "ok", "error", 1);
    }

    return 0;
}