#include "libs/data_struct/unordered_set/unordered_set.c"
#include <stdio.h>

int main() {
    unordered_array_set set1 = unordered_array_set_create(5);
    unordered_array_set set2 = unordered_array_set_create(5);
    for (int i = 1; i < 4; ++i) {
        unordered_array_set_insert(&set1, i);
    }

    for (int i = 1; i < 4; ++i) {
        unordered_array_set_insert(&set2, i);
    }

    outputArray_(set1.data, 3);
    outputArray_(set2.data, 3);


    return 0;
}
