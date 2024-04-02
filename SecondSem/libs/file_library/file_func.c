#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../string/task/string_.c"
#include "../data_struct/matrix/matrix.c"
#include "../data_struct/vector/vector.c"


void WriteMatricesBinaryFile(char *file_name, FILE *file, matrix *data,int count_matrices) {
    char *c;
    file = fopen(file_name, "wb");

    c = (char *) data;
    for (int i = 0; i < sizeof(matrix) * count_matrices; i++) {
        putc(*c++, file);
    }

    fclose(file);
}


void SwapMatricesColsAndRowsFile(char *file_name, FILE *file, int count_matrices) {
    char *c;
    int counter;
    int size = sizeof(matrix) * count_matrices;
    matrix *ptr = malloc(size);
    file = fopen(file_name, "rb");
        c = (char *) ptr;

        while ((counter = getc(file)) != EOF) {
            *c = counter;
            c++;
        }

        for (int j = 0; j < count_matrices; ++j) {
            transposeMatrix(&ptr[j]);
        }

        c = (char *) ptr;
        for (int i = 0; i < sizeof(matrix) * count_matrices; i++) {
            putc(*c++, file);
        }
    fclose(file);
    free(ptr);
}

void OutputMatricesInFile(char *file_name, FILE *file, int count_matrices) {
    char *c;
    int counter;
    int size = sizeof(matrix) * count_matrices;
    matrix *ptr = malloc(size);
    file = fopen(file_name, "rb");
    c = (char *) ptr;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }

    outputMatrices(ptr, count_matrices);
    fclose(file);
    free(ptr);
}


void check_Correct_Open_File(FILE *f) {
    if (f == NULL) {
        printf("errno %d\n", errno);
        perror("f");
        exit(1);
    }
}

char *getWayByTasks(char *filename) {
    char *way = __FILE__;
    char *sub_way = str_replace("tasks/F", "F", filename);
    return str_replace(way, __FILE_NAME__, sub_way);
}

