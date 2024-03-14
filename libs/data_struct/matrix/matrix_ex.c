#include <math.h>
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
        *m = multiplicationMatrix(*m, *m);
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


int *getRowPredicateArray(matrix m, int (Predicate)(int *, int)) {
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

/* Задание 7. Найти сумму максимальных элементов всех псевдодиагоналей
данной матрицы */

int Max2(int a, int b) {
    return a > b ? a : b;
}

int Min2(int a, int b) {
    return a < b ? a : b;
}

void CreateArrayMaxValuesDiagonals(matrix m, int *a) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            a[i + j] = Max2(a[i + j], m.values[m.nRows - 1 - i][j]);
        }
    }
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int count_diagonals = m.nRows + m.nCols - 1;
    int a[count_diagonals];

    for (int i = 0; i < count_diagonals; ++i) {
        a[i] = 0;
    }

    CreateArrayMaxValuesDiagonals(m, a);

    long long sum = 0;

    for (int i = 0; i < count_diagonals; ++i) {
        sum += a[i];
    }

    int main_diagonal = m.values[0][0];

    for (int i = 1; i < Min2(m.nRows, m.nCols); ++i) {
        main_diagonal = Max2(m.values[i][i], main_diagonal);
    }

    sum -= main_diagonal;

    return sum;
}

// 8 Задание.

int GetMinBeforeMax(matrix m, position pmax) {
    int min = INT_MAX;
    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < pmax.rowIndex - abs(pmax.colIndex - i) + 1; ++j) {
            min = Min2(min, m.values[j][i]);
        }
    }
    return min;
}

int task8(matrix m) {
    position pmax = getMaxValuePos(m);

    return GetMinBeforeMax(m, pmax);
}

//9 Задание. Дано 𝑛 точек в 𝑚-мерном пространстве. Упорядочить точки по неубыванию их расстояний до начала координат.

float getSumSq(int *a, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(a[i], 2);
    return sum;
}

float getDistance(int *a, int n) {
    return sqrtf(getSumSq(a, n));
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; i++) {
        int j = i;
        while (j > 0 && criteria(m.values[j - 1], m.nCols) > criteria(m.values[j], m.nCols)) {
            float *temp = m.values[j];
            m.values[j] = m.values[j - 1];
            m.values[j - 1] = (int *) temp;
            j--;
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

/* 10 Задание. Определить количество классов эквивалентных строк данной прямоугольной
матрицы. Строки считать эквивалентными, если равны суммы их элементов. */

int cmp_long_long(const void *pa, const void *pb) {
    long long a = *(long long *) pa;
    long long b = *(long long *) pb;
    return (a > b) - (a < b);
}

int countNUnique(long long *a, int n) {
    int count = 1;
    qsort(a, n, sizeof(long long), cmp_long_long);
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1])
            count++;
    }
    return count;
}

int countEqClassesByRowsSum(matrix m) {
    long long *row_sum[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            row_sum[i] += m.values[i][j];

    }
    int unique_sums = countNUnique(row_sum, m.nRows);
    return unique_sums;
}

/* 11 Задание.Дана матрица. Определить 𝑘 – количество "особых" элементов матрицы, считая
элемент "особым" , если он больше суммы остальных элементов своего столбца */

int getNSpecialElement(matrix m) {
    int counter = 0;
    for (int i = 0; i < m.nRows; i++) {
        int max_rows = GetMaxInRows(m.values[i], m.nCols);
        int sum = GetSum(m.values[i], m.nCols) - max_rows;
        if (max_rows > sum)
            counter++;
    }
    return counter;
}

/* 12 Задание Дана квадратная матрица. Заменить предпоследнюю строку матрицы первым
из столбцов, в котором находится минимальный элемент матрицы.*/

position getLeftMin(matrix m) {
    position p_min = getMinValuePos(m);
    return p_min;
}

void swapPenultimateRow(matrix m, int n) {
    int i = 0, j = 0;
    position p_min = getLeftMin(m);
    while (i < m.nRows && j < m.nCols) {
        int temp = m.values[m.nRows - 2][j];
        m.values[m.nRows - 2][j] = m.values[i][p_min.colIndex];
        m.values[i][p_min.colIndex] =  temp;
        i++;
        j++;
    }
}

/*  13 Задание. Дан массив матриц одного размера.
 Определить число матриц, строки которых упорядочены по неубыванию элементов */

bool isNonDescendingSorted(int *a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1])
            return false;
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; i++) {
        if (hasAllNonDescendingRows(ms[i]))
            count++;
    }
    return count;
}