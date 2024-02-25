#include "vector_void.h"

void append_v(void* *a , size_t *n , void* value ) {
    a [* n ] = value ;
    (*n)++;
}


//проверка на то, является ли вектор полным
bool isFullV(vector_void *v) {
    return v->size == v->capacity;
}

//проверка на то, является ли вектор пустым
bool isEmptyV(vector_void *v) {
    return v->size == 0;
}

void checkCorrectMemory_V(vector_void *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
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
        v->data = (void *) realloc(v->data, sizeof(int) * newCapacity);
        v->capacity = newCapacity;
        if (v->size > newCapacity) {
            v->size = newCapacity;
        }
    }
    checkCorrectMemory_V(v);
}

void extensionMemoryVector_V(vector_void *v) {
    if (v->capacity == 0) {
        v->data = (void *) realloc(v->data, v->baseTypeSize);
        v->capacity = 1;
    } else if (isFullV(v)) {
        v->data = (void *) realloc(v->data, v->baseTypeSize * v->capacity * 2);
        v->capacity *= 2;
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

//добавляет элемент в конец вектора
void pushBackV(vector_void *v, void* source) {
    extensionMemoryVector_V(v);
    append_v(v->data, &v->size, source);
}

//удаляет элемент с конца вектора
void popBackV(vector_void *v);

// записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vector_void *v, size_t index, void* destination);

//записывает на index-ый элемент вектора v значение, расположенное по
//адресу source
void setVectorValueV(vector_void *v, size_t index, void* source);

