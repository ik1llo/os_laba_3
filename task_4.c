#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/utsname.h>

#define DEFAULT_BUFFER_SIZE 127

void show_help() {
    printf("available commands:\n");
    printf("stop - exits the program\n");
    printf("-h, --help - get help\n");
    printf("-b, --buffer - command's buffer\n");
}

void clean_exit() {
    printf("3 seconds to be exited...\n");
    sleep(3);

    printf("\033[H\033[J");
}

int main(int argc, char *argv[]) {
    int buffer_size = DEFAULT_BUFFER_SIZE;
    char *buffer;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            show_help();
            return 0;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) {
            if (i + 1 < argc) { buffer_size = atoi(argv[++i]); } 
            else { return 1; }
        }
    }

    struct utsname uinfo;
    uname(&uinfo);

    buffer = (char *)malloc(buffer_size);
    if (!buffer) { return 1; }

    while (1) {
        printf("[%s]$ ", uinfo.nodename);
        if (fgets(buffer, buffer_size, stdin) == NULL) {
            clean_exit();
            break;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "stop") == 0) {
            free(buffer);
            buffer = NULL;

            clean_exit();

            break;
        } else if (strlen(buffer) > 0) { system(buffer); }
    }

    if (buffer != NULL) { free(buffer); }

    return 0;
}
