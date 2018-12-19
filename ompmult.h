#include "matrix.h"

#ifndef EP_OMPMULT_H
#define EP_OMPMULT_H

// realiza a multiplicacao das matrizes 'A' por 'B transposta' utizando OpenMP
matrix *omp_mult_matrix_by_matrix(matrix *A, matrix *B);

#endif //EP_OMPMULT_H
