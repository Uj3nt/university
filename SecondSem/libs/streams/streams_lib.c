#include "../file_library/file_func.c"

void generateSubMatrixArray(int size_main_matrix, matrix sub_matrix_array) {
    srand(time(NULL));

    for (int i = 0; i < sub_matrix_array.nRows; ++i) {
        sub_matrix_array.values[i][0] = rand() % size_main_matrix;
        sub_matrix_array.values[i][1] = rand() % size_main_matrix;

        sub_matrix_array.values[i][2] = sub_matrix_array.values[i][0] + rand() % (size_main_matrix - sub_matrix_array.values[i][0]);
        sub_matrix_array.values[i][3] = sub_matrix_array.values[i][1] + rand() % (size_main_matrix - sub_matrix_array.values[i][1]);
    }
}

void updateMatrixSubMatrices(matrix main_matrix, matrix sub_matrix_array) {
    for (int i = 0; i < sub_matrix_array.nRows; ++i) {
        for (int j = sub_matrix_array.values[i][0]; j <= sub_matrix_array.values[i][2]; ++j) {
            for (int k = sub_matrix_array.values[i][1]; k <= sub_matrix_array.values[i][3]; ++k) {
                main_matrix.values[j][k] += 1;
            }
        }
    }
}

int getCountNeighbour(matrix m, int i, int j) {
    int i_plus = i + 1, i_minus = i - 1, j_plus = j + 1, j_minus = j - 1, sum = 0;

    i_minus = i_minus < 0 ? m.nRows - 1 : i_minus;
    j_minus = j_minus < 0 ? m.nCols - 1 : j_minus;
    i_plus = i_plus < m.nRows ? i_plus : 0;
    j_plus = j_plus < m.nRows ? j_plus : 0;

    sum += m.values[i_minus][j];
    sum += m.values[i_plus][j];
    sum += m.values[i_minus][j_minus];
    sum += m.values[i_plus][j_minus];
    sum += m.values[i_minus][j_plus];
    sum += m.values[i_plus][j_plus];
    sum += m.values[i][j_minus];
    sum += m.values[i][j_plus];


    return sum;
}

void lifeGameStep(matrix m) {
    matrix buf = getMemMatrix(m.nRows, m.nCols);

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            buf.values[i][j] = getCountNeighbour(m, i, j);
        }
    }

    outputMatrix(buf);

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (buf.values[i][j] < 2) {
                m.values[i][j] = 0;
            } else if (buf.values[i][j] == 3 && m.values[i][j] == 0) {
                m.values[i][j] = 1;
            } else if  (buf.values[i][j] > 3 && m.values[i][j] == 1)  {
                m.values[i][j] = 0;
            }
        }
    }
    freeMemMatrix(&buf);
}

void medianFilter3(matrix m) {
    int size = 0;
    int a[9];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != 1 | j != 1) {
                a[size++] = m.values[i][j];
            }
        }
    }
    SelectionArraySort(a, size);
    outputArray_(a, 8);
    m.values[1][1] = a[size/2];
}



typedef struct Domain {
    char *way;
    int count_used;
} Domain;

Domain *getMemDomainArray(int n) {
    Domain *values = (Domain *) malloc(n * sizeof(Domain));
    return values;
}

Domain getDomain(char *s) {
    Domain domain;
    WordDescriptor word;

    getWordReverse(getEndOfString(s), s, &word);

    domain.count_used = atoi(s);
    domain.way = word.begin;

    return domain;
}

void addSubDomainInArray(Domain *res, int *size_res, char *way, int count_used) {
    Domain domain;
    int is_new_domain = 1;

    for (int i = 1; i <= *size_res; ++i) {
        if (!strcmp(res[i].way, way)) {
            res[i].count_used += count_used;
            is_new_domain = 0;
            break;
        }
    }
    if (is_new_domain) {
        (*size_res)++;
        res[*size_res].count_used = count_used;
        res[*size_res].way = way;
    }
}


void addAllDomain(Domain *res, int *size_res, Domain domain) {
    char *ptrRead = getEndOfString(domain.way);

    while (ptrRead > domain.way) {
        if (*ptrRead == '.') {
            addSubDomainInArray(res, size_res, ptrRead, domain.count_used);
        }
        ptrRead--;
    }
    addSubDomainInArray(res, size_res, ptrRead, domain.count_used);
}
