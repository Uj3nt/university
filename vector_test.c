#include "libs/data_struct/vector/vector.c"


void test_create_vector1() {
    vector v = createVector(3);
    assert(v.size == 0);
    assert(v.capacity == 3);
    deleteVector(&v);
}

void test_create_vector2() {
    vector v = createVector(1);
    assert(v.size == 0);
    assert(v.capacity == 1);
    deleteVector(&v);
}

void test_create_vector3() {
    vector v = createVector(10);
    assert(v.size == 0);
    assert(v.capacity == 10);
    deleteVector(&v);
}

void test_create_vector() {
    test_create_vector1();
    test_create_vector2();
    test_create_vector3();
}

void test_vector_pushBack1() {
    vector v = createVector(4);
    pushBack(&v, 72);
    assert(v.data[0] == 72);
    deleteVector(&v);
}

void test_vector_pushBack2() {
    vector v = createVector(4);
    pushBack(&v, 72);
    pushBack(&v, 13);
    pushBack(&v, 25);
    assert(v.data[2] == 25);
    deleteVector(&v);
}

void test_vector_pushBack3() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    assert(v.data[1] == 12);
    deleteVector(&v);
}

void test_vector_pushBack() {
    test_vector_pushBack1();
    test_vector_pushBack2();
    test_vector_pushBack3();
}

void test_vector_popBack


void test() {
    test_create_vector();
    test_vector_pushBack();
}


int main() {
    test_create_vector();
    test_vector_pushBack();
}