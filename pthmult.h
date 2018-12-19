#include "matrix.h"

#ifndef EP_PTHMULT_H
#define EP_PTHMULT_H

typedef struct {
    matrix *A;
    matrix *B;
    matrix *C;
    long long start;
    long long finish;
} parameters;

// realiza a multiplicacao da matriz 'A' por 'B transposta' utizando Pthreads
matrix *pthread_mult_matrix_by_matrix(matrix *A, matrix *B);

#endif //EP_PTHMULT_H
