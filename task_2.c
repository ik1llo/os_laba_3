#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("enter a command...\n");
        return 1;
    }

    char command[1024] = "";
    for (int k = 1; k < argc; k++) {
        strcat(command, argv[k]);
        if (k < argc - 1) {
            strcat(command, " ");
        }
    }

    char* cmd = strtok(command, ";");
    while (cmd != NULL) {
        printf("command: %s\n", cmd);
        int return_code = system(cmd);
        printf("command return code: %d\n\n", return_code);

        cmd = strtok(NULL, ";");
    }

    return 0;
}
