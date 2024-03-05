#include "matrix.h"

/* Задание 1  Дана квадратная матрица, все элементы которой различны. Поменять местами
строки, в которых находятся максимальный и минимальный элементы. */

void swapMinMaxRows(matrix *m) {
    position maxValuePos = getMaxValuePos(*m);
    position minValuePos = getMinValuePos(*m);
    swapRows(*m, minValuePos.rowIndex, maxValuePos.rowIndex);
}