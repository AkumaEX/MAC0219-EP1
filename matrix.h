#ifndef EP_MATRIX_H
#define EP_MATRIX_H

typedef struct {
    unsigned long lin;
    unsigned long col;
    double **val;
} matrix;

// cria uma matriz de zeros com dimensão especificada
matrix *create_matrix(unsigned long n_lin, unsigned long n_col);

// carrega a matriz do caminho especificado
matrix *load_matrix(char *filepath);

// carrega a matriz de forma transposta do caminho especificado
matrix *load_matrix_t(char *filepath);

// salva a matriz no caminho especificado
void save_matrix(char *filepath, matrix *m);

// desaloca a matriz da memoria
void destroy_matrix(matrix *m);

#endif //EP_MATRIX_H
