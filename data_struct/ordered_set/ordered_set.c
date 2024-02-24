# ifndef INC_ORDERED_ARRAY_SET_H
# define INC_ORDERED_ARRAY_SET_H

# include <stdint.h>
# include <assert.h>
# include <memory.h>
# include <stdio.h>
# include <stdbool.h>
# include "ordered_set.h"
# include "../../algorithms/array/array.c"
#include "../unordered_set/unordered_set.c"

typedef struct ordered_array_set {
    int *data; // элементы множества
    size_t size; // количество элементов в множестве
    size_t capacity; // максимальное количество элементов в множестве
} ordered_array_set;

int ordered_array_set_in(unordered_array_set *set, int value) {
    return binarySearch_(set->data,set->size, value) != set->size;
};

void ordered_array_set_update_size( ordered_array_set *set) {
    if (set->size != set->capacity) {
        set->data = (int*) realloc(set->data, sizeof(int)*set->size);
        set->capacity = (size_t) set->data;
    }
}

//возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set) {
            malloc(sizeof(int) * capacity), 0, capacity
    };
}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    qsort(&a, size, sizeof(int), compare_ints);

    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; ++i) {
        append_(&set.data ,&set.size, a[i]);
    }
    ordered_array_set_update_size(&set);
    return set;

}


// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    return (!memcmp(set1.data, set2.data, set1.size));
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set);

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value) {
    int pos = binarySearchMoreOrEqual_(set->data, set->size, value);
    insert_(set->data, set->size, pos,  value);
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    int pos = binarySearchMoreOrEqual_(set->data, set->size, value);
    deleteByPosSaveOrder_(set->data, set->size, pos);
}

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2);

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        if (binarySearch_(set2.data, set2.size, set1.data[i]) != set1.size) {
            ordered_array_set_insert(&set, set1.data[i]);
        }
    }

    for (int i = 0; i < set2.size; ++i) {
        if (binarySearch_(set1.data, set1.size, set2.data[i]) != set2.size) {
            ordered_array_set_insert(&set, set2.data[i]);
        }
    }

    return set;
}

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        if (binarySearch_(set2.data, set2.size, set1.data[i]) == set1.size) {
            ordered_array_set_insert(&set, set1.data[i]);
        }
    }

    return set;
}

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        if (binarySearch_(set2.data, set2.size, set1.data[i]) == set1.size) {
            ordered_array_set_insert(&set, set1.data[i]);
        }
    }

    for (int i = 0; i < set2.size; ++i) {
        if (binarySearch_(set1.data, set1.size, set2.data[i]) == set2.size) {
            ordered_array_set_insert(&set, set2.data[i]);
        }
    }

    return set;
}



// возвращает дополнение до универсума universumSet множества set
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    return ordered_array_set_difference(universumSet,set);
}

// вывод множества set
void ordered_array_set_print(ordered_array_set set) {
    outputArray_(set.data, set.size);
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete(ordered_array_set set) {
    free(set.data);
}

# endif