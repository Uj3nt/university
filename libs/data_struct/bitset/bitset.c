# ifndef INC_BITSET_H
# define INC_BITSET_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "bitset.h"
#include <stdint.h>

typedef struct bitset {
    uint32_t values; // множество
    uint32_t maxValue; // максимальный элемент универсума
} bitset;


int bitset_checkValue(bitset *a, unsigned value) {
    return value >= 0 && value <= a->maxValue;
}

bitset bitset_create(unsigned maxValue) {
    assert(maxValue < 32);
    bitset set = {0, maxValue};
    return set;
}

bool bitset_in(bitset set, unsigned int value) {
    return (set.values & (1 << value)) >> value;
}

bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values;
}

bool bitset_isSubset(bitset subset, bitset set) {
    return set.values & subset.values == subset.values;
}

void bitset_insert(bitset *set, unsigned int value) {
    set->values | (1 << value);
}

void bitset_deleteElement(bitset *set, unsigned int value) {
    set->values & ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    uint32_t maxSize = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    bitset set = {set1.values | set2.values, maxSize};
}

bitset bitset_intersection(bitset set1, bitset set2) {
    uint32_t maxSize = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    bitset set = {set1.values & set2.values, maxSize};
    return set;
}

bitset bitset_difference(bitset set1, bitset set2) {
    uint32_t maxSize = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    bitset set = {set1.values & ~set2.values, maxSize};
    return set;
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    uint32_t maxSize = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    bitset set = {set1.values ^ set2.values, maxSize};
    return set;
}

bitset bitset_complement(bitset set) {
    set.maxValue = (~(set.values << (32 - set.maxValue))) >> (32 - set.maxValue);
    return set;
}

void bitset_print(bitset set) {
    for (int i = 0; i < set.maxValue; ++i) {
        if (set.values << i & 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

#endif