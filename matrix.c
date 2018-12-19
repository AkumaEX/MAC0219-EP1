#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

// cria uma matriz de zeros com dimensão especificada
matrix *create_matrix(unsigned long n_lin, unsigned long n_col) {
    unsigned long i;
    matrix *m = malloc(sizeof(matrix));
    m->lin = n_lin;
    m->col = n_col;
    m->val = (double **) calloc(m->lin, sizeof(double *));

    for (i = 0; i < m->lin; i++)
        m->val[i] = (double *) calloc(m->col + 1, sizeof(double));

    return m;
}

// carrega a matriz do caminho especificado
matrix *load_matrix(char *filepath) {
    unsigned long i, j;
    double v;
    matrix *m;
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Unable to read file, exiting...\n");
        exit(1);
    }

    if (!fscanf(file, "%lu", &i)) {
        printf("Unable to read file, exiting...\n");
        exit(1);
    }
    if (!fscanf(file, "%lu", &j)) {
        printf("Unable to read file, exiting...\n");
        exit(1);
    }

    m = create_matrix(i, j);

    while (true) {
        if (fscanf(file, "%lu", &i) == EOF) break;
        if (fscanf(file, "%lu", &j) == EOF) break;
        if (fscanf(file, "%lf", &v) == EOF) break;
        m->val[i-1][j-1] = v;
    }

    fclose(file);
    return m;
}

// carrega a matriz de forma transposta do caminho especificado
matrix *load_matrix_t(char *filepath) {
    unsigned long i, j;
    double v;
    matrix *m;
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Unable to read file, exiting...\n");
        exit(1);
    }

    if (!fscanf(file, "%lu", &i)) {
        printf("Unable to read file, exiting...\n");
        exit(1);
    }
    
    if (!fscanf(file, "%lu", &j)) {
        printf("Unable to read file, exiting...\n");
        exit(1);
    }

    m = create_matrix(j, i);

    while (true) {
        if (fscanf(file, "%lu", &i) == EOF) break;
        if (fscanf(file, "%lu", &j) == EOF) break;
        if (fscanf(file, "%lf", &v) == EOF) break;
        m->val[j-1][i-1] = v;
    }

    fclose(file);
    return m;
}


// salva a matriz no caminho especificado
void save_matrix(char *filepath, matrix *m) {
    unsigned long i, j;
    FILE *file = fopen(filepath, "w");
    fprintf(file, "%lu %lu\n", m->lin, m->col);

    for (i = 0; i < m->lin; i++)
        for (j = 0; j < m->col; j++)
            fprintf(file, "%lu %lu %lf\n", i + 1, j + 1, m->val[i][j]);

    fclose(file);
}


// desaloca a matriz da memoria
void destroy_matrix(matrix *m) {
    unsigned long i;

    for (i = 0; i < m->lin; i++)
        free(m->val[i]);
    free(m->val);
    free(m);
}
