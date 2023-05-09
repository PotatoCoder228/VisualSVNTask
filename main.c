#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "app.h"
#include "time.h"

int main(int argc, char **argv) {
    printf("App started\n");
    fflush(stdout);
    time_t start, end;
    if (argc < 3) {
        printf("Incorrect cmd args.\n");
        return EXIT_FAILURE;
    }
    exception_s *exception = new_exception();
    if (exception == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    time(&start);
    int flag = app_start(argv[1], argv[2], exception);
    time(&end);
    if(flag != EXIT_FAILURE) {
        printf("Program reversed file from %lld seconds\n", end - start);
    }
    exception_destroy(exception);
    printf("App finished\n");
    fflush(stdout);
    return EXIT_SUCCESS;
}