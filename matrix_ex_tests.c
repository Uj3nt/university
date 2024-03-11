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
                    3, 2, 5, 4,
                    1, 3, 6, 3,
                    3, 2, 1, 2
            },
            3, 4
    );


    printf("%lld",findSumOfMaxesOfPseudoDiagonal(test_matrix1));
}