#include "../streams_lib.c"

void task1() {
    int size_main_matrix = 3;
    int count_submatrix = 2;
    matrix pos_array = getMemMatrix(count_submatrix, 4);
    generateSubMatrixArray(size_main_matrix, pos_array);
    outputMatrix(pos_array);
    matrix main_matrix = getMemMatrix(size_main_matrix, size_main_matrix);
    updateMatrixSubMatrices(main_matrix, pos_array);
    outputMatrix(main_matrix);
}

void task2() {
    matrix m = getMemMatrix(4, 3);
    inputMatrix(&m);
    outputMatrix(m);
    lifeGameStep(m);
    outputMatrix(m);
}

void task3() {
    matrix m = getMemMatrix(3, 3);
    inputMatrix(&m);
    outputMatrix(m);
    medianFilter3(m);
    outputMatrix(m);
}

void task4() {
    Domain domain;
    int size_test_data = 4;
    char *s[] = { "900 google.mail.com", "50yahoo.com", "1 intel.mail.com", "5 wiki.org"};
    Domain *res = getMemDomainArray(10);
    int size = 0;

    for (int i = 0; i < size_test_data; ++i) {
        domain = getDomain(s[i]);
        addAllDomain(res, &size, domain);
    }

    for (int i = 1; i <= size; ++i) {
        printf("%d %s\n", res[i].count_used, res[i].way);
    }
}

void task5() {
    matrix m = getMemMatrix(3, 3);
    inputMatrix(&m);
    printf("%d", GetCountUnitSubMatrices(m));
}

void  task6() {
    printf("%d",GetMinNumByPattern("DDD"));
}

void task7() {
    int size = 6;
    int a[] = {3,2,1,6,0, 5};
    int *res = (int *)calloc(size * 2, sizeof(int));
    for (int i = 1; i < size * 2; ++i) {
        res[i] = -1;
    }

    getBinTree(a, size, res, 1);

    for (int i = 1; i < size * 2; ++i) {
        printf("%d ", res[i]);
    }
    free(res);
}

void task8() {
    char s[] = "abap";
    int indices[] = {0, 3, 2, 1};
    int indicesSize = 4;

    char* resString = makeStringFromIndeces(s, indices, indicesSize);

    printf("%s\n", resString);

    free(resString);
}

void task9() {
    srand(time(NULL));

    int N;

    scanf("Input N: %d ", &N);

    int count_num = 10;
    char *way_input = getWayByTasks("task9input.txt");
    FILE *file_input = fopen(way_input, "w");
    GenerateRandomIntNumbers(file_input, count_num);
    fclose(file_input);

    int numbers[count_num];
    fopen(way_input, "r");
    ReadIntNumbers(file_input, numbers, &count_num);
    fclose(file_input);

    for (int i = 0; i < count_num; i++) {
        if (numbers[i] >= N)
            deleteByPosSaveOrder_(numbers, &count_num, i);
    }

    char *way_output = getWayByTasks("task9output.txt");
    FILE *file_output = fopen(way_output, "w");
    WriteIntNumbers(file_output, numbers, count_num);
    fclose(file_output);
}

void task10() {
    int part;
    char *way_input = getWayByTasks("task10last.txt");
    generateRandomStrings("task10last.txt");
    FILE *file = fopen(way_input, "r");
    scanf("%d", &part);
    while (getch() == 3) {
        outputPartsText(part, file);
    }
    fclose(file);
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
    //task9();
    task10();
}