#include "../file_func.c"

void task1() {
    char *name = "task1.txt";
    char *way = getWayByTasks(name);

    int count_matrices = 3;
    int values[] = {1, 2, 3,
                    1, 2, 3,
                    1, 2, 3,

                    5, 6, 7,
                    5, 6, 7,
                    5, 6, 7,

                    8, 9, 0,
                    8, 9, 0,
                    8, 9, 0 };

    matrix *matrix_array = createArrayOfMatrixFromArray(values, 3, 3, 3);

    FILE file;
    WriteMatricesBinaryFile(way, &file, matrix_array,count_matrices);
    SwapMatricesColsAndRowsFile(way, &file, count_matrices);
    OutputMatricesInFile(way, &file, count_matrices);
}

void task2() {
    srand(time(NULL));

    int count_num = 10;
    char *way_input = getWayByTasks("task2input.txt");
    FILE *file_input = fopen(way_input, "w");
    GenerateRandomFloatNumbers(file_input, count_num);
    fclose(file_input);

    double numbers[count_num];
    fopen(way_input, "r");
    ReadFloatNumbers(file_input, numbers, &count_num);
    fclose(file_input);

    char *way_output = getWayByTasks("task2output.txt");
    FILE *file_output = fopen(way_output, "w");
    WriteFloatNumbers(file_output, numbers, count_num);
    fclose(file_output);
}

void task3() {
    srand(time(NULL));

    char *way_input = getWayByTasks("task3.txt");
    FILE *file = fopen(way_input, "w");
    WriteGenerateExpression(file);
    fclose(file);

    fopen(way_input, "r");
    int res =  CalculateExpressionFromFile(file);
    fclose(file);

    fopen(way_input, "a");
    fprintf(file," = %d", res);
    fclose(file);

}

void task4() {
    generateRandomWords("task4input.txt");
    printCorrectWords("task4input.txt", "task4output.txt", "a");
}

void task5() {
    generateRandomStrings("task5input.txt");
    printMaxLenWordsInString("task5input.txt", "task5output.txt");
}

void task6() {
    generatePolinomialArray("task6.txt", 10, 4);
    printPalinomialWithFile("task6.txt", 10, 4);
    printCorrectPalinomial("task6.txt", 1, 10, 4);
    printPalinomialWithFile("task6.txt", 10, 4);

}

void task7() {
    int size = 10;
    int a[size];
    generateArray(a, size);
    outputArray_(a, size);
    generateArrayBinaryFile("task7.txt", a, size);
    sortArrayInFile("task7.txt", size);
    outputArrayFromFile("task7.txt", size);
}

void task8() {
    char *name = "task8.txt";
    char *way = getWayByTasks(name);
    FILE file;
    int count_matrices = 3;
    int values[] = {1, 2, 3,
                    2, 2, 3,
                    3, 3, 3,

                    5, 6, 7,
                    5, 6, 7,
                    5, 6, 7,

                    8, 9, 0,
                    8, 9, 0,
                    8, 9, 0 };

    matrix *matrix_array = createArrayOfMatrixFromArray(values, 3, 3, 3);

    WriteMatricesBinaryFile(way, &file, matrix_array,count_matrices);
    transpocseMatrixIfNotSymetricFile(way, &file, count_matrices);
    OutputMatricesInFile(way, &file, count_matrices);
}

void task9() {
    int size_team = 5;
    int count_sportsmens = 10;
    Sportsman *array = getMemForSportsmensArray(count_sportsmens);
    genereteSportsmens(array, count_sportsmens);
    writeSportsmensInFile("task9.txt", array, count_sportsmens);
    outputSportsmensFromFile("task9.txt", count_sportsmens);
    printf("\n");
    getBestTeam("task9.txt",size_team,count_sportsmens);

}


int main() {
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    //task6();
    //task7();
    //task8();
    task9();
}