#include "filesystem.h"
#include <string.h>
#include <ctype.h>

void print_help() {
    printf("\nAvailable commands:\n");
    printf("  create <name> <content>  - Create file\n");
    printf("  add_image <name> <path>  - Add image reference\n");
    printf("  view <name>              - View file\n");
    printf("  modify <name> <content>  - Modify file\n");
    printf("  delete <name>            - Delete file\n");
    printf("  list                     - List files\n");
    printf("  help                     - Show help\n");
    printf("  exit                     - Exit\n\n");
}

void list_files(FILE* fs) {
    rewind(fs);
    char line[256];
    printf("\nFiles:\n");
    while (fgets(line, sizeof(line), fs)) {
        if (line[0] == '/') {
            line[strcspn(line, "\n")] = 0;
            printf("  %s\n", line+1);
        }
    }
}

int main() {
    FILE* fs = fs_open("disk.filesystem");
    if (!fs) return 1;

    char cmd[20], filename[100], content[1024];

    printf("proectFS Shell. Type 'help' for commands\n");
    while (1) {
        printf("> ");
        if (scanf("%19s", cmd) != 1) {
            while (getchar() != '\n');
            continue;
        }

        for (char *p = cmd; *p; ++p) *p = tolower(*p);
if (strcmp(cmd, "create") == 0) {
            scanf("%99s %1023[^\n]", filename, content);
            fs_create(fs, filename, content);
        }
        else if (strcmp(cmd, "add_image") == 0) {
            scanf("%99s %1023[^\n]", filename, content);
            char img_entry[1200];
            snprintf(img_entry, sizeof(img_entry), "IMAGE|PATH:%s", content);
            fs_create(fs, filename, img_entry);
        }
        else if (strcmp(cmd, "view") == 0) {
            scanf("%99s", filename);
            fs_view(fs, filename);
        }
        else if (strcmp(cmd, "modify") == 0) {
            scanf("%99s %1023[^\n]", filename, content);
            fs_modify(fs, filename, content);
        }
        else if (strcmp(cmd, "delete") == 0) {
            scanf("%99s", filename);
            fs_delete(fs, filename);
        }
        else if (strcmp(cmd, "list") == 0) {
            list_files(fs);
        }
        else if (strcmp(cmd, "help") == 0) {
            print_help();
        }
        else if (strcmp(cmd, "exit") == 0) {
            break;
        }
        else {
            printf("Unknown command\n");
        }
    }

    fs_close(fs);
    return 0;
}
