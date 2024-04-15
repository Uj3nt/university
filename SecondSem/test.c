#include <stdio.h>
#include <malloc.h>

#define MAX_SIZE_SET 50

void insert_(int *const a, int *n, int pos, int value) {
    if (*n != 0) {
        size_t lowBound = (pos == 0) ? SIZE_MAX : pos;
        (*n)++;
        for (size_t i = *n; i != lowBound; i--)
            a[i] = a[i - 1];
        a[pos] = value;
    } else {
        (*n)++;
        a[pos] = value;
    }
}

static int binarySearch_(const int *a, int x, int right, int left) {
    if (left > right)
        return -1;
    int middle = (left + right) / 2;
    if (a[middle] == x)
        return middle;
    else if (a[middle] < x)
        return binarySearch_(a, x, right, middle + 1);
    else
        return binarySearch_(a, x, middle - 1, left);
}

int binarySearch(const int *a, int n, int x) {
    return binarySearch_(a, x, n - 1, 0);
}

int binarySearchMoreOrEqual_(int *a, int n, int x) {
    if (a[0] >= x)
        return 0;
    size_t left = 0;
    size_t right = n;

    while (right - left > 1) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle;
        else
            right = middle;
    }
    return right;
}

typedef struct set {
    int data[MAX_SIZE_SET];
    int size;
} set;

void outputSet(set s) {
    printf("{");
    for (int i = 0; i < s.size; ++i) {
        printf("%d ", s.data[i]);
    }
    printf("}\n");
}

void insertSet(set *s, int value) {
    int pos = binarySearchMoreOrEqual_(s->data, s->size, value);
    if (s->data[pos] != value) {
        if (pos == s->size) {
            s->data[s->size++] = value;
        } else {
            insert_(s->data, &s->size, pos, value);
        }
    }
}

set And(set s1, set s2) {
    set s_res = {.size = 0};

    for (int i = 0; i < s1.size; ++i) {
        for (int j = 0; j < s2.size; ++j) {
            if (s1.data[i] == s2.data[j]) {
                s_res.data[s_res.size++] = s1.data[i];
            }
        }
    }
    return s_res;
}


set Or(set s1, set s2) {
    set s_res = s1;

    for (int i = 0; i < s2.size; ++i) {
        insertSet(&s_res, s2.data[i]);
    }
    return s_res;
}

set Dif(set s1, set s2) {
    set res = s1;
    for (int i = 0; i < s2.size; ++i) {
        int pos = binarySearch(res.data, res.size, s2.data[i]);
        if (pos != -1) {
            for (int j = pos; j < res.size - 1; ++j) {
                res.data[j] = res.data[j + 1];
            }
            res.size--;
        }
    }
    return res;
}

set SymDif(set s1, set s2) {
    return Or(Dif(s1, s2), Dif(s2, s1));
}


int isEqualSet(set s1, set s2) {
    if (s1.size == s2.size) {
        for (int i = 0; i < s1.size; ++i) {
            if (s1.data[i] != s2.data[i]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}


set *getPowerSet(set U) {
    int power_set_size = 1 << (U.size);
    set *power_set = (set *) malloc(power_set_size * sizeof(set));
    for (int i = 0; i < power_set_size; ++i) {
        set s = {
                .size = 0
        };

        for (int j = 0; j < U.size; j++) {
            if (i & (1 << j)) {
                insertSet(&s, U.data[j]);
            }
        }
        power_set[i] = s;
    }

    return power_set;
}

void outputWoods(set U, set A, set B, set C) {
    set *power_set = getPowerSet(U);
    int noHaveWoods = 0;
    for (int i = 0; i < 1 << (U.size); ++i) {
        set X = power_set[i];

        set set1 = Or(And(A, X), Dif(X, B));
        set set2 = Dif(And(X,Dif(U, B)), C);
        if (isEqualSet(set1, set2)) {
            outputSet(X);
            noHaveWoods = 1;
        }
    }
    if (!noHaveWoods) {
        printf("No have Woods");
    }
    free(power_set);
}

int main() {
    set U = {
            .data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            .size = 10
    };

    set A = {
            .data = {2, 3, 4, 7, 10},
            .size = 4
    };

    set B = {
            .data = {1, 2, 6, 9},
            .size = 4
    };

    set C = {
            .data = {3, 5, 7, 9},
            .size = 4
    };

    outputWoods(U, A, B, C);
}