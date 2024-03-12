#include <assert.h>
#include "libs/data_struct/matrix/matrix.c"
#include "libs/data_struct/matrix/matrix_ex.c"


int main() {
    matrix test_matrix2 = createMatrixFromArray(
            (int[]) {
                    7, 5, 1,
                    2, 1, 2,
                    4, 3, 4
            },
            3, 3
    );

    matrix test_matrix1 = createMatrixFromArray(
            (int[]) {
                    10, 7, 5, 6,
                    3, 11, 8, 9,
                    4, 1, 12, 2
            },
            3, 4
    );

position pmax = getMaxValuePos(test_matrix1);
    printf("%d", GetMinBeforeMax(test_matrix1, pmax));
}