#ifndef SMALL_H
#define SMALL_H

#include <stdint.h>
#include "params.h"

/* Small coefficients: elements of F3 = {-1, 0, 1} */
typedef small small_t;

/* Reduce to canonical representative mod 3 (-1, 0, 1) */
static inline small_t F3_freeze(int16_t x) {
    return (small_t)(x - 3 * ((10923 * x + 16384) >> 15));
}

/* Add/sub/mul in F3 */
static inline small_t F3_add(small_t a, small_t b) {
    return F3_freeze((int16_t)a + (int16_t)b);
}

static inline small_t F3_sub(small_t a, small_t b) {
    return F3_freeze((int16_t)a - (int16_t)b);
}

static inline small_t F3_mul(small_t a, small_t b) {
    return F3_freeze((int16_t)a * (int16_t)b);
}

#endif /* SMALL_H */
