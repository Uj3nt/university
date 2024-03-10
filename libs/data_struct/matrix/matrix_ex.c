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
минимальных элементов столбцов: */

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

/* Задание 4. Если данная квадратная матрица A симметрична, то заменить A**2. */

matrix multiplicationMatrix(matrix m1, matrix m2) {
    matrix res_m = getMemMatrix(m1.nRows, m1.nCols);

    for (int i = 0; i < m1.nRows; ++i) {
        for (int j = 0; j < m1.nCols; ++j) {
            res_m.values[i][j] = 0;
            for (int k = 0; k < m1.nRows; ++k) {
                res_m.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return res_m;
}

void task4(matrix *m) {
    if (isSquareMatrix(m)) {
        *m = multiplicationMatrix(*m,*m);
    } else {
        printf("is not Square matrix");
    }
}

/* Задание 5. Дана квадратная матрица. Если среди сумм элементов строк матрицы нет равных, то транспонировать матрицу.. */

int isUnique(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int GetSum(int *a, int n) {
    int sum = 0;

    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }

    return sum;
}


int* getRowPredicateArray(matrix m, int (Predicate) (int*, int)) {
    int PredicateArray[m.nRows];
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            PredicateArray[i] = Predicate(m.values[i], m.values[i][j]);
        }
    }
    return PredicateArray;
}


void task5(matrix *m) {
    int *SumArray[m->nRows];
    *SumArray = getRowPredicateArray(*m, GetSum);

    if (isUnique(SumArray, m->nRows)) {
        transposeMatrix(m);
    } else {
        printf("Have Ununique sum rows");
    }
}

/* Задание 6. Даны две квадратные матрицы 𝐴 и 𝐵. Определить, являются ли они взаимно
обратными (𝐴 = 𝐵−1)  */

int IsInversMatrix(matrix m1, matrix m2) {
    matrix m = getMemMatrix(m1.nRows, m1.nCols);
    return isEMatrix(&m);
}
