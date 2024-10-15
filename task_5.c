#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <getopt.h>  

#define DEFAULT_FILE_NAME "output"
#define DEFAULT_NUMBERS 5

void generate_random_numbers (const char* file_name, int num) {
    FILE *file = fopen(file_name, "w");
    if (!file)
        exit(EXIT_FAILURE);

    for (int k = 0; k < num; k++)
        fprintf(file, "%f\n", (float)rand() / RAND_MAX);
    fclose(file);
}

int main (int argc, char* argv[]) {
    char*   file_name = NULL;
    int     children_count = 0;
    int     opt;
    
    while ((opt = getopt(argc, argv, "f:n:")) != -1) {
        switch (opt) {
            case 'f':
                file_name = optarg;
                break;
            case 'n':
                children_count = atoi(optarg);
                break;
            default:
                fprintf(stderr, "usage: %s [-f file_name] [-n number_of_children]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!file_name) {
        file_name = getenv("FILE_NAME");
        if (!file_name)
            file_name = DEFAULT_FILE_NAME;
    }

    if (children_count <= 0)
        children_count = DEFAULT_NUMBERS;

    for (int k = 0; k < children_count; k++) {
        pid_t pid = fork();
        if (pid == 0) {
            char child_file_name[256];
            snprintf(child_file_name, sizeof(child_file_name), "%s_%d.txt", file_name, k + 1);
            generate_random_numbers(child_file_name, k + 1);

            exit(0);
        } else if (pid < 0) { exit(EXIT_FAILURE); }
    }

    for (int k = 0; k < children_count; k++)
        wait(NULL);

    return 0;
}
