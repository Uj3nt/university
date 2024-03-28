# ifndef INC_UNORDERED_ARRAY_SET_H
# define INC_UNORDERED_ARRAY_SET_H


# include <assert.h>
# include <malloc.h>

# include "unordered_set.h"
# include "../../algorithms/array/array.c"

typedef struct unordered_array_set {
    int * data ; // элементы множества
    size_t size ; // количество элементов в множестве
    size_t capacity ; // максимальное количество элементов в множестве
} unordered_array_set ;

void unordered_array_set_is_able(unordered_array_set *set) {
    assert(set->size < set->capacity);
}


// возвращает пустое множество для capacity элементов++
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {
            malloc(sizeof(int) * capacity), 0, capacity
    };
}

int unordered_array_set_in(unordered_array_set *set, int value) {
    return linearSearch_(set->data,set->size, value);
};



void unordered_array_set_insert(unordered_array_set *set, int element) {
    if (unordered_array_set_in(set, element) == set->size) {
        append_(set->data, &set->size, element);
    }
}


void unordered_array_set_update_size( unordered_array_set *set) {
    if (set->size != set->capacity) {
        set->data = (int*) realloc(set->data, sizeof(int)*set->size);
        set->capacity = (size_t) set->data;
    }
}

// возвращает множество, состоящее из элементов массива a размера size.
unordered_array_set unordered_array_set_create_from_array( const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; ++i) {
        unordered_array_set_insert(&set, a[i]);
    }
    unordered_array_set_update_size(&set);
    return set;
}


// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
int unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    int counter = 0;
    if (set1.size == set2.size) {
        for (int i = 0; i < set1.size; ++i) {
            if (linearSearch_(set2.data, set2.size, (set1.data[i])) != set1.size) {
                counter++;
            }
        }
    }
    return counter == set1.size;
}



// удаляет элемент value из множества set
void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t pos = linearSearch_(set->data, set->size, value);
    deleteByPosSaveOrder_(set->data, &set->size, pos);
}

// возвращает объединение множеств set1 и set2.
unordered_array_set unordered_array_set_union( unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        unordered_array_set_insert(&set, set1.data[i]);
    }

    for (int i = 0; i < set2.size; ++i) {
        unordered_array_set_insert(&set, set2.data[i]);
    }
    return set;
}

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection( unordered_array_set set1, unordered_array_set set2 ) {
    unordered_array_set set = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        if (linearSearch(set2.data, set2.size, set1.data[i]) != -1) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }

    for (int i = 0; i < set2.size; ++i) {
        if (linearSearch(set1.data, set1.size, set2.data[i]) != -1) {
            unordered_array_set_insert(&set, set2.data[i]);
        }
    }

    return set;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        if (linearSearch(set2.data, set2.size, set1.data[i]) == -1) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }

    return set;
}


// возвращает дополнение до универсума множества set25
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    return unordered_array_set_difference(universumSet,set);
}

// возвращает симметрическую разность множеств set1 и set226
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; ++i) {
        if (linearSearch(set2.data, set2.size, set1.data[i]) == -1) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }

    for (int i = 0; i < set2.size; ++i) {
        if (linearSearch(set1.data, set1.size, set2.data[i]) == -1) {
            unordered_array_set_insert(&set, set2.data[i]);
        }
    }

    return set;
}

// вывод множества set
void unordered_array_set_print(unordered_array_set set) {
    outputArray_(set.data, set.size);
}

// освобождает память, занимаемую множеством set
void unordered_array_set_delete ( unordered_array_set set ) {
    free(set.data);
}

# endif