#include "libs/data_struct/matrix/matrix.c"


int main() {
    matrix m = getMemMatrix(4, 3);
    inputMatrix(&m);
    outputMatrix(m);
    swapColumns(m,0,2);
    outputMatrix(m);
    return 0;
}