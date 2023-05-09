//
// Created by sasha on 07.05.2023.
//
#include "reverser.h"
#include "stdlib.h"

static void swap(int8_t *a, int8_t *b) {
    int8_t buf = *b;
    *b = *a;
    *a = buf;
}

static bool reverse_block(int8_t *array, size_t size) {
    if (array == NULL) {
        return false;
    }
    for (int64_t i = 0; i < size / 2; i++) {
        swap(&(array[i]), &(array[size - i - 1]));
    }
    return true;
}

enum rvrs_consts {
    BLOCK_SIZE = 500000
};


#ifndef _WIN32

#include <unistd.h>

bool reverse(FILE *in, FILE *out) {
    if (in == NULL || out == NULL) {
        return false;
    }
    int64_t flag = fseeko(in, 0, SEEK_END);
    if (flag == -1) {
        return false;
    }
    int64_t bytes = ftello(in);
    if (bytes == -1) {
        return false;
    }
    printf("File size: %ld bytes\n", bytes);
    fflush(stdout);
    int8_t *symbols = malloc(sizeof(int8_t) * BLOCK_SIZE);
    if (!symbols) {
        return false;
    }
    for (int64_t offset = -BLOCK_SIZE; offset >= (-bytes); offset -= BLOCK_SIZE) {
        flag = fseeko(in, offset, SEEK_END);
        if (flag == -1) {
            free(symbols);
            return false;
        }
        flag = (int64_t) fread(symbols, sizeof(int8_t), BLOCK_SIZE, in);
        if (flag == -1) {
            free(symbols);
            return false;
        }
        if (!reverse_block(symbols, flag)) {
            free(symbols);
            return false;
        }
        flag = (int64_t) fwrite(symbols, sizeof(int8_t), flag, out);
        if (flag == -1) {
            free(symbols);
            return false;
        }
    }
    flag = fseeko(in, 0, SEEK_SET);
    if (flag == -1) {
        free(symbols);
        return false;
    }
    flag = (int64_t) fread(symbols, sizeof(int8_t), bytes % BLOCK_SIZE, in);
    if (flag == -1) {
        free(symbols);
        return false;
    }
    if (!reverse_block(symbols, flag)) {
        free(symbols);
        return false;
    }
    flag = (int64_t) fwrite(symbols, sizeof(int8_t), flag, out);
    if (flag == -1) {
        free(symbols);
        return false;
    }
    free(symbols);
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
    printf("File size: %lld bytes\n", bytes);
    fflush(stdout);
    int8_t *symbols = malloc(sizeof(int8_t) * BLOCK_SIZE);
    if (!symbols) {
        return false;
    }
    for (int64_t offset = -BLOCK_SIZE; offset >= (-bytes); offset -= BLOCK_SIZE) {
        flag = _fseeki64(in, offset, SEEK_END);
        if (flag == -1) {
            free(symbols);
            return false;
        }
        flag = (int64_t) fread(symbols, sizeof(int8_t), BLOCK_SIZE, in);
        if (flag == -1) {
            free(symbols);
            return false;
        }
        if (!reverse_block(symbols, flag)) {
            free(symbols);
            return false;
        }
        flag = (int64_t) fwrite(symbols, sizeof(int8_t), flag, out);
        if (flag == -1) {
            free(symbols);
            return false;
        }
    }
    flag = _fseeki64(in, 0, SEEK_SET);
    if (flag == -1) {
        free(symbols);
        return false;
    }
    flag = (int64_t) fread(symbols, sizeof(int8_t), bytes%BLOCK_SIZE, in);
    if (flag == -1) {
        free(symbols);
        return false;
    }
    if (!reverse_block(symbols, flag)) {
        free(symbols);
        return false;
    }
    flag = (int64_t) fwrite(symbols, sizeof(int8_t), flag, out);
    if (flag == -1) {
        free(symbols);
        return false;
    }
    free(symbols);
    return true;
}

#endif