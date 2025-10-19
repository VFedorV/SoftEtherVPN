#ifndef FQ_H
#define FQ_H

#include <stdint.h>
#include "params.h"

/* Fq represents elements of Z/qZ, typically in range (-q/2, q/2] */
typedef Fq FqElement;

/* Freeze: reduce integer x modulo q into canonical representative */
static inline FqElement Fq_freeze(int32_t x) {
    int32_t t = x % PARAM_Q;
    if (t < 0) t += PARAM_Q;
    if (t > PARAM_Q / 2) t -= PARAM_Q;
    return (FqElement)t;
}

/* Addition in Fq */
static inline FqElement Fq_add(FqElement a, FqElement b) {
    return Fq_freeze((int32_t)a + (int32_t)b);
}

/* Subtraction in Fq */
static inline FqElement Fq_sub(FqElement a, FqElement b) {
    return Fq_freeze((int32_t)a - (int32_t)b);
}

/* Multiplication in Fq */
static inline FqElement Fq_mul(FqElement a, FqElement b) {
    return Fq_freeze((int32_t)a * (int32_t)b);
}

#endif /* FQ_H */
