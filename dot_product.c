#include "dot_product.h"
#include <smmintrin.h>

// realiza o produto escalar entre dois vetores 'a' e 'b' de tamanho 'size'
double dot_product(double *a, double *b, unsigned long size) {
    unsigned long i;
    __m128d av, bv, mul, sum;
    sum = _mm_setzero_pd();

    for (i = 0; i < size; i += 2) {
        av = _mm_load_pd(&a[i]);
        bv = _mm_load_pd(&b[i]);
        mul = _mm_dp_pd(av, bv, 0xFF);
        sum = _mm_add_pd(sum, mul);
    }
    return _mm_cvtsd_f64(sum);
}
