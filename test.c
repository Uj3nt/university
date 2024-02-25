#include "libs/algorithms/array/array.c"
#include "libs/data_struct/unordered_set/unordered_set.c"


int main() {
    //ex1
    unordered_array_set set_A =
            unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 6 , 7}, 6);
    unordered_array_set set_B =
            unordered_array_set_create_from_array((int[]) {1, 3, 6, 7}, 4);
    unordered_array_set set_C =
            unordered_array_set_create_from_array((int[]) {3, 4, 5, 6,8}, 5);

    unordered_array_set symetric_diff_set = unordered_array_set_symmetricDifference(set_B, set_C);
    unordered_array_set union_set = unordered_array_set_union(set_B,set_C);
    unordered_array_set diff_set1 = unordered_array_set_difference(set_A,symetric_diff_set);
    unordered_array_set diff_set2 = unordered_array_set_difference(symetric_diff_set,set_A);
    unordered_array_set last_set = unordered_array_set_union(diff_set1, diff_set2);

    printf("task 1:\n");
    unordered_array_set_print(last_set);

    //ex2
    unordered_array_set set_A2 =
            unordered_array_set_create_from_array((int[]) {1, 2, 3, 8}, 4);
    unordered_array_set set_B2 =
            unordered_array_set_create_from_array((int[]) {3, 6, 7}, 3);
    unordered_array_set set_C2 =
            unordered_array_set_create_from_array((int[]) {2, 3, 4, 5, 7}, 5);

    unordered_array_set union_set2 = unordered_array_set_union(set_A2, set_B2);
    unordered_array_set difference_set2 = unordered_array_set_difference(union_set2, set_C2);
    unordered_array_set intersection_set = unordered_array_set_intersection(set_A2, set_B2);
    unordered_array_set last_set2 = unordered_array_set_union(intersection_set, difference_set2);

    printf("task 2:\n");
    unordered_array_set_print(last_set2);
    return 0;
}
