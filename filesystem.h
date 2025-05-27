#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

FILE* fs_open(const char* filename);
void fs_close(FILE* fs);

// Операции с файлами
void fs_create(FILE* fs, const char* filename, const char* content);
void fs_insert(FILE* fs, const char* filename);
void fs_modify(FILE* fs, const char* filename, const char* new_content);
void fs_delete(FILE* fs, const char* filename);

// Вспомогательные функции
int fs_exists(FILE* fs, const char* filename);

#endif
