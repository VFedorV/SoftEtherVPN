#ifndef UTIL_MASKS_H
#define UTIL_MASKS_H

#include <stdint.h>

/* return -1 if x!=0; else 0 */
static inline int int16_nonzero_mask(int16_t x) {
    uint16_t u = (uint16_t)x;
    uint32_t v = u;
    v = ~v + 1;
    v >>= 31;
    return -(int)v;
}

/* return -1 if x<0; else 0 */
static inline int int16_negative_mask(int16_t x) {
    uint16_t u = (uint16_t)x;
    u >>= 15;
    return -(int)u;
}

#endif /* UTIL_MASKS_H */
