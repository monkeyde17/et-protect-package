#include "xxhash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ETProtectData.h"

void print_help() {
    printf("usage : hash -f ./filename -s 0x12345678 -t ./dir/filename\n");
}

char* read_from_file(const char *path, ssize_t *size) {
    FILE* pFile = fopen(path, "rb");

    if (pFile == NULL) {
        printf("error : no such %s file\n", path);
        exit(-2);
    }

    long lSize = 0;
    fseek(pFile, 0 ,SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);


    char *buf = (char*)malloc(sizeof(char) * lSize);

    if (buf == NULL) {
        fclose(pFile);
        exit(-1);
    }

    *size = fread(buf, 1, lSize, pFile);

    if (*size != lSize) {
        free(buf);
        buf = NULL;
    }


    fclose(pFile);

    return buf;
}

void clean_file(char *buf) {
    free(buf);
}

unsigned int get_hash_code(const char *path, unsigned int seed) {
    ssize_t size = 0;
    char *buf = read_from_file(path, &size);

    unsigned int re = XXH32(buf, size, seed);

    clean_file(buf);

    return re;
}

void write_to_file(const char *filename, unsigned int value) {
    FILE *pFile = fopen(filename, "wb+");

    if (pFile == NULL) {
        printf("error : no such %s file\n", filename);
        exit(-2);
    }

    ETProtectData buf;
    buf.setHashValue(value);

    fwrite((char *)(&buf), sizeof(ETProtectData), sizeof(char), pFile);

    fclose(pFile);
}

int main(int argc, char const *argv[]) {

    unsigned int seed = 0x12345678;
    const char *path = NULL;
    const char *dest = NULL;

    int i = 0;

    while (++i < argc) {
        if (strcmp(argv[i], "-f") == 0) {
            path = argv[i + 1];
        } else if (strcmp(argv[i], "-s") == 0 ) {
            sscanf(argv[i + 1], "%d", &seed);
        } else if (strcmp(argv[i], "-t") == 0) {
            dest = argv[i + 1];
        }
    }


    if (path == NULL) {
        print_help();
        exit(-1);
    }

    printf("[Log] path : %s\n", path);
    printf("[Log] dest : %s\n", dest);
    printf("[Log] seed : %x\n", seed);

    unsigned int value = get_hash_code(path, seed);

    printf("[Log] hash : %x\n", value);

    write_to_file(dest, value);	

    return 0;
}
