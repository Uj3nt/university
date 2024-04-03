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


int main() {
    //task1();
    task2();
}