#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int _handler = 0;

void handler(void) {
    printf("handler #%d started\n", _handler);
    sleep(1);

    printf("handler #%d finished\n\n", _handler);
    _handler--;
}

int main(int argc, char *argv[]) {
    if (argc != 2) { return EXIT_FAILURE; }

    int handlers = atoi(argv[1]);
    _handler = handlers;

    for (int k = 0; k < handlers; ++k) {
        if (atexit(handler) != 0) {
            fprintf(stderr, "failed to register handler #%d\n", k + 1);
            return EXIT_FAILURE;
        }
        printf("registered handler #%d\n", k + 1);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
