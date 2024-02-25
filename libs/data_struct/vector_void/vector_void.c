#include "vector_void.h"

//проверка на то, является ли вектор полным
bool isFullV(vector_void *v) {
    return v->size == v->capacity;
}

void checkCorrectMemory_V(vector_void *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void append_v(void* *a , size_t *n , void* value ) {
    a[*n] = value;
    (*n)++;
}

//проверка на то, является ли вектор пустым
bool isEmptyV(vector_void *v) {
    return v->size == 0;
}
//antonio
void pushBackV(vector_void *v, void* source) {
    if (v->size >= v->capacity) {
        size_t curr_size = v->size == 0 ? 1 : v->size * 2;
        reserveV(v, curr_size);
    }
    void* dest = (void*) v->data + v->size * v->baseTypeSize;
    memcpy(dest, source, v->baseTypeSize);
    v->size++;
}


//возвращает структуру-дескриптор вектор из n значений.
vector_void createVectorV(size_t n, size_t baseTypeSize) {
    vector_void vv = {
            (int *) malloc(n * baseTypeSize),
            0,
            n
    };
    checkCorrectMemory_V(&vv);

    return vv;
}

//изменяет количество
//памяти, выделенное под хранение элементов вектора.
void reserveV(vector_void *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
        v->size = 0;
    } else {
        v->data = (void *) realloc(v->data, sizeof(void*) * newCapacity);
        v->capacity = newCapacity;
        if (v->size > newCapacity) {
            v->size = newCapacity;
        }
    }
    checkCorrectMemory_V(v);
}



//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vector_void *v) {
    v->size = 0;
}

//освобождает память, выделенную под
//неиспользуемые элементы.
void shrinkToFitV(vector_void *v) {
    if (!isFullV(v)) {
        v->data = (void *)realloc(v->data, v->baseTypeSize * v->size);
        v->capacity = v->size;
    }
}

//освобождает память, выделенную вектору.
void deleteVectorV(vector_void *v) {
    free(v->data);
}

//удаляет элемент с конца вектора
void popBackV(vector_void *v) {
    (v->size)--;
}

void getVectorValueV(vector_void *v, size_t index, void *destination) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of range");
        exit(1);
    }

    void* dest = (void*) v->data + v->size * v->baseTypeSize;
    memcpy(dest, dest, v->baseTypeSize);
}

void setVectorValueV(vector_void *v, size_t index, void *source) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of range");
        exit(1);
    }

    void* dest = (void*) v->data + v->size * v->baseTypeSize;
    memcpy(dest, source, v->baseTypeSize);
}