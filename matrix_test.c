#include "libs/data_struct/matrix/matrix.c"


int main() {
    matrix m = getMemMatrix(3, 3);
    inputMatrix(&m);
    outputMatrix(m);
    insertionSortRowsMatrixByRowCriteria(m, GetSumRows);
    outputMatrix(m);
    return 0;
}