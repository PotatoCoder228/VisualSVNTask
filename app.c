//
// Created by sasha on 08.05.2023.
//

#include <errno.h>
#include <string.h>
#include "app.h"
#include "reverser.h"

int app_start(char *in_name, char *out_name, exception_s *exception) {
    if (in_name == NULL || out_name == NULL) {
        throw_exception(exception, NULL_POINTER_ERROR, "NULL среди in_name||out_name в app_start.");
        return EXIT_FAILURE;
    }

    FILE *in = fopen(in_name, "rb");
    if (in == NULL) {
        throw_exception(exception, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    FILE *out = fopen(out_name, "wb");
    if (out == NULL) {
        throw_exception(exception, errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if (!reverse(in, out)) {
        throw_exception(exception, errno, "Can't reverse bytes.");
        return EXIT_FAILURE;
    }
    int flag = fclose(in);
    if (flag == -1) {
        throw_exception(exception, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    flag = fclose(out);
    if (flag == -1) {
        throw_exception(exception, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}