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


void test_vector_popBack1() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    popBack(&v);
    assert(v.size == 2);
    deleteVector(&v);
}

void test_vector_popBack2() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    popBack(&v);
    popBack(&v);
    popBack(&v);
    assert(v.size == 0);
    deleteVector(&v);

}

void test_vector_popBack3() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    popBack(&v);
    popBack(&v);
    popBack(&v);
    pushBack(&v, 33);
    popBack(&v);
    assert(v.size == 0);
    deleteVector(&v);
}


void test_vector_pushBack() {
    test_vector_pushBack1();
    test_vector_pushBack2();
    test_vector_pushBack3();
}

void test_vector_popBack() {
    test_vector_popBack1();
    test_vector_popBack2();
    test_vector_popBack3();
}


void test_vector_getValue1() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    int x = getVectorValue(&v, 2);
    assert(x == 33);
}

void test_vector_getValue2() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    int x = getVectorValue(&v, 1);
    assert(x == 12);
}

void test_vector_getValue3() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    int x = getVectorValue(&v, 0);
    assert(x == 72);
}

void test_vector_getValue() {
    test_vector_getValue1();
    test_vector_getValue2();
    test_vector_getValue3();
}
void test() {
    test_create_vector();
    test_vector_pushBack();
    test_vector_popBack();
    test_vector_getValue();
}


int main() {
    test();
}