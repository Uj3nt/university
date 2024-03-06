#include "matrix.h"

/* Задание 1  Дана квадратная матрица, все элементы которой различны. Поменять местами
строки, в которых находятся максимальный и минимальный элементы. */

void swapMinMaxRows(matrix m) {
    position maxValuePos = getMaxValuePos(m);
    position minValuePos = getMinValuePos(m);
    swapRows(m, minValuePos.rowIndex, maxValuePos.rowIndex);
}

void task1(matrix m) {
    swapMinMaxRows(m);
}

/* Задание 2 Упорядочить строки матрицы по неубыванию наибольших элементов строк: */

int GetMaxInRows(int *a, int n) {
    int max_value = a[0];

    for (int i = 1; i < n; ++i) {
        max_value = max_value > a[i] ? max_value : a[i];
    }

    return max_value;
}

void task2(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, GetMaxInRows);
}