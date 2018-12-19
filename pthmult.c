#include "pthmult.h"
#include "dot_product.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8

// devolve uma estrutura de parametros
parameters *get_parameters(matrix *A, matrix *B, matrix *C, unsigned long start, unsigned long finish) {
    parameters *p = malloc(sizeof(parameters));
    p->A = A;
    p->B = B;
    p->C = C;
    p->start = start;
    p->finish = finish;
    return p;
}

// realiza a multiplicacao da parte da matriz 'A' por 'B transposta'
void *mult_partial_matrix_by_matrix(void *args) {
    parameters *p = (parameters *) args;
    unsigned long i, j;

    for (i = p->start; i < p->A->lin && i < p->finish; i++)
        for (j = 0; j < p->B->lin; j++)
            p->C->val[i][j] = dot_product(p->A->val[i], p->B->val[j], p->B->col);

    free(p);
    return NULL;
}

// realiza a multiplicacao da matriz 'A' por 'B transposta'
matrix *pthread_mult_matrix_by_matrix(matrix *A, matrix *B) {
    unsigned long i, num_jobs;
    int thread_id = 0;
    matrix *C = create_matrix(A->lin, B->lin);
    pthread_t thread[NUM_THREADS];
    num_jobs = (A->lin / NUM_THREADS) + 1;

    for (i = 0; i < A->lin; i += num_jobs) {
        parameters *params = get_parameters(A, B, C, i, i + num_jobs);

        if (pthread_create(&thread[thread_id], NULL, &mult_partial_matrix_by_matrix, (void *) params)) {
            printf("Unable to create thread, exiting...\n");
            exit(1);
        }

        thread_id++;
    }

    for (i = 0; i < thread_id; i++) {
        if (pthread_join(thread[i], NULL)) {
            printf("Unable to join thread, exiting...\n");
            exit(1);
        }
    }

    return C;
}