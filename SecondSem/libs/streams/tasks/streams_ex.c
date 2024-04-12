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

int main() {
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    task6();
}