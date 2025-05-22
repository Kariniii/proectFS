#include "filesystem.h"
#include <string.h>
#include <stdlib.h>

// Проверка существования файла
static int file_exists(FILE* fs, const char* filename) {
    rewind(fs);
    char line[256];
    while (fgets(line, sizeof(line), fs)) {
        if (strncmp(line+1, filename, strlen(filename)) == 0 && line[0] == '/') {
            return 1;
        }
    }
    return 0;
}

FILE* fs_open(const char* filename) {
    FILE* fs = fopen(filename, "a+");
    if (!fs) {
        perror("Error opening filesystem");
    }
    return fs;
}

void fs_close(FILE* fs) {
    if (fs) fclose(fs);
}

void fs_create(FILE* fs, const char* filename, const char* content) {
    if (file_exists(fs, filename)) {
        printf("Error: File '%s' already exists\n", filename);
        return;
    }
    fseek(fs, 0, SEEK_END);
    fprintf(fs, "/%s\n%s\n/\n", filename, content);
    fflush(fs);
}

void fs_view(FILE* fs, const char* filename) {
    rewind(fs);
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fs) {
        if (strstr(line, filename) && line[0] == '/') found = 1;
        else if (found && line[0] == '/') break;
        else if (found) printf("%s", line);
    }
    if (!found) printf("File not found\n");
}

void fs_modify(FILE* fs, const char* filename, const char* new_content) {
    if (!file_exists(fs, filename)) {
        printf("Error: File '%s' not found\n", filename);
        return;
    }
    
    char buffer[4096] = {0};
    rewind(fs);
    char line[256];
    int skip = 0;
    
    while (fgets(line, sizeof(line), fs)) {
        if (strstr(line, filename) && line[0] == '/') skip = 1;
        else if (skip && line[0] == '/') skip = 0;
        if (!skip) strcat(buffer, line);
    }
    
    strcat(buffer, "/");
    strcat(buffer, filename);
    strcat(buffer, "\n");
    strcat(buffer, new_content);
    strcat(buffer, "\n/\n");
    
    freopen(NULL, "w", fs);
    fputs(buffer, fs);
    fflush(fs);
}

void fs_delete(FILE* fs, const char* filename) {
    fs_modify(fs, filename, "");
}
