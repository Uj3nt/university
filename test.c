#include "libs/data_struct/vector_void/vector_void.c"

int main() {
    vector_void vv = createVectorV(3, sizeof(int));
    reserveV(&vv, 9);
    printf("%d\n", vv.capacity);
    vv.size = 9;

    int x = 1;
    pushBackV(&vv, &x);
    pushBackV(&vv, &x);
    pushBackV(&vv, &x);
    printf("%d\n", vv.capacity);


    printf("SUCSE");
    return 0;

}