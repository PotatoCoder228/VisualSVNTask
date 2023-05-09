//
// Created by sasha on 07.05.2023.
//

#include "reverser.h"

#ifndef _WIN32

#include <unistd.h>

bool reverse(FILE *in, FILE *out) {
    if (in == NULL || out == NULL) {
        return false;
    }
    __off_t flag = fseeko(in, 0, SEEK_END);
    if (flag == -1) {
        return false;
    }
    __off_t bytes = ftello(in);
    if (bytes == -1) {
        return false;
    }
    for (__off_t offset = -1; offset >= (-bytes); --offset) {
        flag = fseeko(in, offset, SEEK_END);
        if (flag == -1) {
            return false;
        }
        int8_t byte[1];
        flag = (__off_t) fread(byte, sizeof(int8_t), 1, in);
        if (flag == -1) {
            return false;
        }
        flag = (__off_t) fwrite(byte, sizeof(int8_t), 1, out);
        if (flag == -1) {
            return false;
        }
    }
    return true;
}

#else

bool reverse(FILE *in, FILE *out) {
    if (in == NULL || out == NULL) {
        return false;
    }
    int64_t flag = _fseeki64(in, 0, SEEK_END);
    if (flag == -1) {
        return false;
    }
    int64_t bytes = _ftelli64(in);
    if (bytes == -1) {
        return false;
    }
    for (int64_t offset = -1; offset >= (-bytes); --offset) {
        flag = _fseeki64(in, offset, SEEK_END);
        if (flag == -1) {
            return false;
        }
        int8_t byte[1];
        flag = (int64_t) fread(byte, sizeof(int8_t), 1, in);
        if (flag == -1) {
            return false;
        }
        flag = (int64_t) fwrite(byte, sizeof(int8_t), 1, out);
        if (flag == -1) {
            return false;
        }
    }
    return true;
}

#endif