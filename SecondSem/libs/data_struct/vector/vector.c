#ifndef INC_VECTOR_H
#define INC_VECTOR_H

#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "vector.h"
#include "../../algorithms/array/array.c"

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

//проверка на то, является ли вектор полным
bool isFull(vector *v) {
    return v->size == v->capacity;
}

//проверка на то, является ли вектор пустым
bool isEmpty(vector *v) {
    return v->size == 0;
}


//check_correct_memory
void checkCorrectMemory_(vector *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}


//возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n) {
    vector v = {
            (int *) malloc(n * sizeof(int)),
            0,
            n
    };
    checkCorrectMemory_(&v);

    return v;
}

//изменяет количество
//памяти, выделенное под хранение элементов вектора.
void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
        v->size = 0;
    } else {
        v->data = (int *) realloc(v->data, sizeof(int) * newCapacity);
        v->capacity = newCapacity;
        if (v->size > newCapacity) {
            v->size = newCapacity;
        }
    }
    checkCorrectMemory_(v);
}

void extensionMemoryVector_(vector *v) {
    if (v->capacity == 0) {
        v->data = (int *) realloc(v->data, sizeof(int));
        v->capacity = 1;
    } else if (isFull(v)) {
        v->data = (int *) realloc(v->data, sizeof(int) * v->capacity * 2);
        v->capacity *= 2;
    }
    checkCorrectMemory_(v);
}

//удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector *v) {
    v->size = 0;
}

//освобождает память, выделенную под неиспользуемые элементы.
void shrinkToFit(vector *v) {
    if (!isFull(v)) {
        v->data = (int *) realloc(v->data, sizeof(int) * v->size);
        v->capacity = v->size;
    }
}

//освобождает память, выделенную вектору.
void deleteVector(vector *v) {
    free(v->data);
}

//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

//добавляет элемент в конец вектора
void pushBack(vector *v, int x) {
    extensionMemoryVector_(v);
    append_(v->data, &v->size, x);
}

//удаляет элемент с конца вектора
void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    } else {
        deleteByPosSaveOrder_(v->data, &v->size, v->size);
    }
}

// возвращает указатель на
//index-ый элемент вектора.
int *atVector(vector *v, size_t index) {
    return v->data + index - 1;
}

//возвращает указатель на последний элемент вектора.
int *back(vector *v) {
    return v->data + v->size -1;
}


# endif