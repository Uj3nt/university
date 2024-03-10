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
                    0, 0, 0,
                    1, 2, 1,
                    1, 1, 7
            },
            3, 3
    );



    outputMatrix(test_matrix1);
}