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

//check_correct_memory
void checkCorrectMemory(vector *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}


//возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n) {
    vector v = {
            (int *) malloc(n * sizeof(int)),
            n,
            n
    };
    checkCorrectMemory(&v);

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
    checkCorrectMemory(v);
}

//удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector *v) {
    v->size = 0;
}

//освобождает память, выделенную под неиспользуемые элементы.
void shrinkToFit(vector *v) {
    if (v->size != v->capacity) {
        v->data = (int *) realloc(v->data, sizeof(int) * v->size);
        v->capacity = v->size;
    }
}

//освобождает память, выделенную вектору.
void deleteVector(vector *v) {
    free(v->data);
}

//проверка на то, является ли вектор пустым
bool isEmpty(vector *v);

//проверка на то, является ли вектор полным
bool isFull(vector *v);

//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i);

//добавляет элемент в конец вектора
void pushBack(vector *v, int x);

//удаляет элемент с конца вектора
void popBack(vector *v);

// возвращает указатель на
//index-ый элемент вектора.
int *atVector(vector *v, size_t index);

//возвращает указатель на последний элемент вектора.
int *back(vector *v);

//возвращает указатель на нулевой элемент вектора.
int *front(vector *v);

# endif