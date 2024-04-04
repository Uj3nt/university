#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
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

void GenerateRandomFloatNumbers(FILE *file, int count) {
    for (int i = 0; i < count; i++) {
        double number = ((double)rand() / RAND_MAX) * 1000.0;
        fprintf(file, "%lf\n", number);
    }
}

void ReadFloatNumbers(FILE *file, double numbers[], int *count) {
    *count = 0;
    while (fscanf(file, "%lf", &numbers[*count]) == 1) {
        (*count)++;
    }
}

void WriteFloatNumbers(FILE *file, double numbers[], int count) {
    for (int i = 0; i < count; i++) {
        fprintf(file, "%.2f\n", numbers[i]);
    }
}

char generateRandomOperator() {
    char operators[] = {'+', '-', '*', '/'};
    return operators[rand() % 4];
}

void WriteGenerateExpression(FILE *file) {
    srand(time(NULL));

    int num1 = (int) rand() % 9 + 1;
    int num2 = (int) rand() % 9 + 1;
    int num3 = (int) rand() % 9 + 1;

    int operantor1  = generateRandomOperator();
    int operantor2  = generateRandomOperator();

    if ((int) rand() % 2) {
        fprintf(file, "%d %c %d %c %d", num1, operantor1, num2, operantor2, num3);
    } else {
        fprintf(file, "%d %c %d", num1, operantor1, num2);
    }
}

int applyOperator(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
    }
}

int CalculateExpressionFromFile(FILE *file) {
    int num1, num2, num3, res;
    num3 = 0;

    char operantor1, operantor2;

    fscanf(file, "%d %c %d %c %d", &num1, &operantor1, &num2, &operantor2, &num3);

    if (num3 == 0) {
        res = applyOperator(operantor1, num1, num2);
    } else {
        if (operantor1 == '/' || operantor1 == '*') {
            res = applyOperator(operantor2, applyOperator(operantor1, num1, num2), num3);
        } else {
            res = applyOperator(operantor1,num1, applyOperator(operantor2, num2, num3));
        }
    }

    return res;
}




