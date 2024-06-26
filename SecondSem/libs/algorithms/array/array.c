# ifndef INC_ARRAY_H
# define INC_ARRAY_H

# include <stdio.h>
# include <assert.h>
# include <stdint.h>
# include "array.h"


void inputArray_ (int * const a , const size_t n ) {
    for ( size_t i = 0; i < n ; i ++)
        scanf ("%d", & a [ i ]) ;
}

void outputArray_ ( const int * const a , const size_t n ) {
    for ( size_t i = 0; i < n ; i ++)
        printf ("%d ", a [ i ]) ;
    printf ("\n") ;
}

void append_ (int * const a , size_t * const n , const int value ) {
    a [* n ] = value ;
    (*n)++;
}

void insert_ (int * const a , int * n , int pos , int value ) {
    assert ( pos < * n ) ;
    if (* n != 0) {
        size_t lowBound = ( pos == 0) ? SIZE_MAX : pos ;
        (* n ) ++;
        for ( size_t i = * n ; i != lowBound ; i --)
            a [ i ] = a [ i - 1];
        a [ pos ] = value ;
    } else {
        (* n ) ++;
        a [ pos ] = value ;
    }
}

void deleteByPosSaveOrder_ (int *a , size_t *n , const size_t pos ) {
    for ( size_t i = pos ; i < * n - 1; i ++)
        a [i] = a [i+1];
    (* n ) --;
}

void deleteByPosUnsaveOrder_ (int *a , size_t *n , size_t pos ) {
    a [ pos ] = a [* n - 1];
    (* n ) --;
}

size_t linearSearch_ ( const int *a , const size_t n , int x ) {
    for ( size_t i = 0; i < n ; i ++)
        if ( a [ i ] == x )
            return i ;
    return n ;
}

int linearSearch( const int *a , size_t n , int x ) {
    for (int i = 0; i < n ; i ++)
        if ( a [ i ] == x )
            return i ;
    return -1;
}

int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}



int any_ ( const int *a , size_t n , int (* predicate ) (int) ) {
    for ( size_t i = 0; i < n ; i ++)
        if ( predicate ( a [ i ]) )
            return 1;
    return 0;
}

int all_ ( const int *a , size_t n , int (* predicate ) (int) ) {
    for ( size_t i = 0; i < n ; i ++)
        if (! predicate ( a [ i ]) )
            return 0;
    return 1;
}

int countIf_ ( const int * const a , const size_t n , int (* predicate ) (int) ){
    int count = 0;
    for ( size_t i = 0; i < n ; i ++)
        count += predicate ( a [ i ]) ;
    return count ;
}

void deleteIf_ (int * const a , size_t * const n , int (* deletePredicate ) (int) ) {
    size_t iRead = 0;
    while ( iRead < * n && ! deletePredicate ( a [ iRead ]) )
        iRead ++;
    size_t iWrite = iRead ;
    while ( iRead < * n ) {
        if (! deletePredicate ( a [ iRead ]) ) {
            a [ iWrite ] = a [ iRead ];
            iWrite ++;
        }
        iRead ++;
    }
    * n = iWrite ;
}

void forEach_ ( const int * source , int * dest , const size_t n , const int (*predicate ) ( int) ) {
    for ( size_t i = 0; i < n ; i ++)
        dest [ i ] = predicate ( source [ i ]) ;
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

int binarySearchMoreOrEqual_ (int *a , int n , int x ) {
    if ( a [0] >= x )
        return 0;
    size_t left = 0;
    size_t right = n ;

    while ( right - left > 1) {
        size_t middle = left + ( right - left ) / 2;
        if ( a [ middle ] < x )
            left = middle ;
        else
            right = middle ;
    }
    return right ;
}

void swapElements(int *a, int pos1, int pos2) {
    int temp = a[pos1];
    a[pos1] = a[pos2];
    a[pos2] = temp;
}

void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void SelectionArraySort(int *a, size_t n) {
    for (int i = 0; i < n; i++) {
        int min_element = a[i];
        int min_element_index = i;

        for (int j = i; j < n; j++) {
            if (a[j] < min_element) {
                min_element = a[j];
                min_element_index = j;
            }
        }
        swapElements(a, i, min_element_index);
    }
}

# endif