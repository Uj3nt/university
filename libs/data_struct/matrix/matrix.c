#include "matrix.h"


//размещает в динамической памяти матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

//освобождает память, выделенную под хранение матрицы m
void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);
    free(m->values);
}


//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);
    free(ms);
}


//ввод матрицы m
void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; ++i) {
        printf("Введите %zu строку\n", i + 1);
        for (int j = 0; j < m->nCols; ++j) {
            scanf("%d", &m->values[i][j]);
        }
    }
}


//ввод массива из nMatrices матриц, хранящейся по адресу ms
void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        inputMatrix(&ms[i]);
    }
}


//вывод матрицы m
void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        printf("\n");
        for (int j = 0; j < m.nCols; ++j) {
            printf("%d ", m.values[i][j]);
        }
    }
    printf("\n");
}


//вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        outputMatrix(ms[i]);
    }
}


//обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2) {
    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}


//обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; ++i) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}



int GetSumRows(int *a, int nCols) {
    int sum_rows = 0;

    for (int i = 0; i < nCols; ++i) {
        sum_rows += a[i];
    }

    return sum_rows;
}

//выполняет сортировку вставками строк матрицы m
//по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *criteria_array = malloc(m.nRows * sizeof(int));

    for (int i = 0; i < m.nRows; i++) {
        criteria_array[i] = criteria(m.values[i], m.nCols);
    }

    for (int i = 1; i < m.nRows; i++) {
        int key = criteria_array[i];
        int *key_row = m.values[i];
        int j = i - 1;

        while (j >= 0 && criteria_array[j] > key) {
            criteria_array[j + 1] = criteria_array[j];
            swapRows(m, j + 1, j);
            j = j - 1;
        }

        criteria_array[j + 1] = key;
        m.values[j + 1] = key_row;
    }

    free(criteria_array);
}


//выполняет сортировку выбором столбцов матрицы m
// по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));


//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

//возвращает значение ’истина’,
//если матрицы m1 и m2 равны, ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }

    return true;
}
// возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае
bool isEMatrix(matrix *m);


//возвращает значение ’истина’,
//если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m);


//транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix *m);


//транспонирует матрицу m
void transposeMatrix(matrix *m);


//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m) {
    int min = m.values[0][0];
    position min_position = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                min_position.rowIndex = i;
                min_position.colIndex = j;
            }
        }
    }

    return min_position;
}

//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m) {
    int max = m.values[0][0];
    position max_position = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                max_position.rowIndex = i;
                max_position.colIndex = j;
            }
        }
    }

    return max_position;
}




//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, int nRows, int nCols);

//возвращает указатель на нулевую матрицу массива из nMatrices матриц,
//размещенных в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);


