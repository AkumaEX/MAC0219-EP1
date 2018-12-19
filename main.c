#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "pthmult.h"
#include "ompmult.h"

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Usage: %s <implementation> <matrix_A_path> <matrix_B_path> <matrix_C_path>\n", argv[0]);
        return 3;
    }

    char *implem = argv[1];
    char *A_path = argv[2];
    char *B_path = argv[3];
    char *C_path = argv[4];

    matrix *A = load_matrix(A_path);
    matrix *B = load_matrix_t(B_path);
    matrix *C;

    if (*implem == 'p') {
        C = pthread_mult_matrix_by_matrix(A, B);
        printf("Using Pthreads\n");
    }
    else if (*implem == 'o') {
        C = omp_mult_matrix_by_matrix(A, B);
        printf("Using OpenMP\n");
    }
    else {
        printf("Unknow implementation, exiting...\n");
        return 3;
    }

    save_matrix(C_path, C);

    destroy_matrix(A);
    destroy_matrix(B);
    destroy_matrix(C);

    return EXIT_SUCCESS;
}