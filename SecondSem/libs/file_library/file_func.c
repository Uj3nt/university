#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include "../string/task/string_.c"
#include "../data_struct/matrix/matrix.c"
#include "../data_struct/vector/vector.c"


typedef struct Polinomial {
    int pow;
    int k;
} Polinomial;


void WriteMatricesBinaryFile(char *file_name, FILE *file, matrix *data, int count_matrices) {
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
        double number = ((double) rand() / RAND_MAX) * 1000.0;
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

    int operantor1 = generateRandomOperator();
    int operantor2 = generateRandomOperator();

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
            res = applyOperator(operantor1, num1, applyOperator(operantor2, num2, num3));
        }
    }

    return res;
}


void generateRandomWords(const char *filename) {
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "w");

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int alphabet_length = strlen(alphabet);

    srand(time(NULL));

    for (int i = 0; i < MAX_N_WORDS_IN_STRING; i++) {
        char word[10];
        int word_length = rand() % (9) + 1;

        for (int j = 0; j < word_length; j++) {
            word[j] = alphabet[rand() % alphabet_length];
        }

        word[word_length] = '\0';
        fprintf(file, "%s\n", word);
    }

    fclose(file);
}

void printCorrectWords(char *inputFilename, char *outputFilename, char *sequence) {
    char *way_input = getWayByTasks(inputFilename);
    FILE *file_input = fopen(way_input, "r");

    char *way_output = getWayByTasks(outputFilename);
    FILE *file_output = fopen(way_output, "w");

    char word[MAX_N_WORDS_IN_STRING];

    while (fscanf(file_input, "%s", word) == 1) {
        if (strstr(word, sequence)) {
            fprintf(file_output, "%s\n", word);
        }
    }

    fclose(file_input);
    fclose(file_output);
}


void generateRandomStrings(char *filename) {
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "w");

    char alphabet[] = " abcdefg hijklm nopqrst uvwxyz ";
    int alphabet_length = strlen(alphabet);

    srand(time(NULL));

    for (int i = 0; i < MAX_N_WORDS_IN_STRING; i++) {
        char word[50];
        int word_length = rand() % (40) + 1;

        for (int j = 0; j < word_length; j++) {
            word[j] = alphabet[rand() % alphabet_length];
        }

        word[word_length] = '\0';
        fprintf(file, "%s\n", word);
    }

    fclose(file);
}

void printMaxLenWordsInString(char *inputFilename, char *outputFilename) {
    char *way_input = getWayByTasks(inputFilename);
    FILE *file_input = fopen(way_input, "r");

    char *way_output = getWayByTasks(outputFilename);
    FILE *file_output = fopen(way_output, "w");

    char s[50];
    while (fgets(s, 50, file_input)) {
        char *begin_search = s;
        char res[50];
        int max_len = 1;
        WordDescriptor word;

        while (getWord(begin_search, &word)) {
            if ((word.end - word.begin + 1) >= max_len) {
                wordDescriptorToString(&word, res);
                max_len = (word.end - word.begin + 1);
            }
            begin_search = word.end;
        }
        fprintf(file_output, "%s\n", res);
    }

    fclose(file_input);
    fclose(file_output);
}

void freePolinomial(Polinomial **array, int nPalinom) {
    for (int i = 0; i < nPalinom; i++) {
        free(array[i]);
    }
    free(array);
}


int generateRandomSign() {
    return rand() % 2 == 0 ? 1 : -1;
}

Polinomial **getMemPalinomeKiller(int nPalinomial, int nMember) {
    Polinomial **array = (Polinomial **) malloc(nPalinomial * sizeof(Polinomial *));
    for (int i = 0; i < nPalinomial; i++) {
        array[i] = (Polinomial *) malloc(nMember * sizeof(Polinomial));
    }
    return (array);
}

void generatePolinomialArray(char *filename, int nPalinomial, int nMember) {
    srand(time(NULL));
    Polinomial **array = getMemPalinomeKiller(nPalinomial, nMember);

    for (int i = 0; i < nPalinomial; ++i) {
        for (int j = 0; j < nMember; ++j) {
            array[i][j].pow = j;
            array[i][j].k = generateRandomSign() * rand() % 9 + 1;
        }
    }

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "wb");

    char *c = (char *) array;
    for (int i = 0; i < sizeof(Polinomial) * nPalinomial * nMember * 2; i++) {
        putc(*c++, file);
    }
    fclose(file);
    freePolinomial(array, nPalinomial);
}



void printCorrectPalinomial(char *filename, int x, int nPalinomial, int nMember) {
    char *c;
    int counter;
    Polinomial **array = getMemPalinomeKiller(nPalinomial, nMember);
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");
    c = (char *) array;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    for (int i = 0; i < nPalinomial; ++i) {
        int res = 0;
        for (int j = 0; j < nMember; ++j) {
            res += (int) pow(x, array[i][j].pow) * array[i][j].k;

        }
        if (res == 0) {
            for (int j = 0; j < nMember; ++j) {
                array[i][j].pow = 0;
                array[i][j].k = 0;
            }
        }
    }

    file = fopen(way, "wb");
    c = (char *) array;
    for (int i = 0; i < sizeof(Polinomial) * nPalinomial * nMember * 2; i++) {
        putc(*c++, file);
    }
    fclose(file);
    freePolinomial(array, nPalinomial);

}

void printPalinomialWithFile(char *filename, int nPalinomial, int nMember) {
    char *c;
    int counter;
    Polinomial **array = getMemPalinomeKiller(nPalinomial, nMember);
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");
    c = (char *) array;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    for (int i = 0; i < nPalinomial; ++i) {
        int res = 0;
        for (int j = 0; j < nMember; ++j) {
            printf("(%dx^%d)",array[i][j].k, array[i][j].pow);
            if (j != nMember - 1) {
                printf(" + ");
            }

        }
        printf("= 0\n");
    }
    printf("\n");

    freePolinomial(array, nPalinomial);
}


void generateArray(int* a, int size) {
    srand(time(NULL));

    int half = size/2;
    int counter_positive = 0, counter_negative = 0, index = 0;

    while (counter_negative < half && counter_positive < half) {
        int random_num = generateRandomSign() * (rand() % 100 + 1);
        a[index++] = random_num;

        if (random_num > 0) {
            counter_positive++;
        } else {
            counter_negative++;
        }
    }

    while (counter_negative < half) {
        int random_num = -1 * (rand() % 100 + 1);
        a[index++] = random_num;
        counter_negative++;
    }

    while (counter_positive < half) {
        int random_num = rand() % 100 + 1;
        a[index++] = random_num;
        counter_positive++;
    }
}

void generateArrayBinaryFile(char *filename,int *a, int size) {
    char *way = getWayByTasks(filename);
    FILE* file = fopen(way, "wb");
    char *c = (char *) a;
    for (int i = 0; i < sizeof(int) * size; i++) {
        putc(*c++, file);
    }
    fclose(file);
}


void sortArrayInFile(char *filename, int size) {
    int counter;
    int a[size];
    char *c = (char *) a;

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    int res[size];
    int positive_index = 0;
    int negative_index = size / 2;
    int index_no_sort_arr = 0;

    while (index_no_sort_arr < size) {
        if (a[index_no_sort_arr] > 0)
            res[positive_index++] = a[index_no_sort_arr++];
        else
            res[negative_index++] = a[index_no_sort_arr++];
    }

    generateArrayBinaryFile(filename, res, size);
}

void outputArrayFromFile(char *filename, int size) {
    int counter;
    int a[size];
    char *c = (char *) a;

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);
    outputArray_(a, size);
}

void transpocseMatrixIfNotSymetricFile(char *file_name, FILE *file, int count_matrices) {
    int counter;
    int size = sizeof(matrix) * count_matrices;
    matrix *ptr = malloc(size);
    file = fopen(file_name, "rb");
    char *c = (char *) ptr;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }

    for (int j = 0; j < count_matrices; ++j)
        if(!isSymmetricMatrix(&ptr[j]))
            transposeMatrix(&ptr[j]);

    c = (char *) ptr;
    for (int i = 0; i < sizeof(matrix) * count_matrices; i++)
        putc(*c++, file);

    fclose(file);
    free(ptr);
}





