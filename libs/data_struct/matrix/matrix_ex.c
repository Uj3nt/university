#include "matrix.h"

/* Задание 1.  Дана квадратная матрица, все элементы которой различны. Поменять местами
строки, в которых находятся максимальный и минимальный элементы. */

void swapMinMaxRows(matrix m) {
    position maxValuePos = getMaxValuePos(m);
    position minValuePos = getMinValuePos(m);
    swapRows(m, minValuePos.rowIndex, maxValuePos.rowIndex);
}

void task1(matrix m) {
    swapMinMaxRows(m);
}

/* Задание 2. Упорядочить строки матрицы по неубыванию наибольших элементов строк: */

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

/* Задание 3. Дана прямоугольная матрица. Упорядочить столбцы матрицы по неубыванию
минимальных элементов столбцов:
 */
int GetMin(int *a, int n) {
    int min_value = a[0];

    for (int i = 1; i < n; ++i) {
        min_value = min_value < a[i] ? min_value : a[i];
    }

    return min_value;
}

void task3(matrix m) {
    selectionSortColsMatrixByColCriteria(m, GetMin);
}