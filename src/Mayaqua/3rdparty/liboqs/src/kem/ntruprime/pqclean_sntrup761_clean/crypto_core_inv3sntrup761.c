#include <stdint.h>
#include <stddef.h>
#include "crypto_core_inv3sntrup761.h"
#include "params.h"

#ifndef PARAM_P
#define PARAM_P 761
#endif

typedef int8_t small;

static int int16_nonzero_mask(int16_t x) {
    uint16_t u = (uint16_t)x;
    uint32_t v = u;
    v = ~v + 1;
    v >>= 31;
    return -(int)v;
}

static int int16_negative_mask(int16_t x) {
    uint16_t u = (uint16_t)x;
    u >>= 15;
    return -(int)u;
}

static small F3_freeze(int16_t x) {
    return (small)(x - 3 * ((10923 * x + 16384) >> 15));
}

int PQCLEAN_SNTRUP761_CLEAN_crypto_core_inv3sntrup761(
    unsigned char *outbytes, const unsigned char *inbytes) {

    const size_t PRIME_SIZE = PARAM_P + 1;
    small *out = (small *)outbytes;
    const small *in = (const small *)inbytes;

    small f[PARAM_P + 1], g[PARAM_P + 1], v[PARAM_P + 1], r[PARAM_P + 1];
    int i, loop, delta;
    int sign, swap, t;

    for (i = 0; i < PARAM_P + 1; ++i) {
        v[i] = 0;
        r[i] = 0;
    }
    r[0] = 1;

    for (i = 0; i < PARAM_P + 1; ++i)
        f[i] = 0;

    f[0] = 1;
    f[PARAM_P - 1] = f[PARAM_P] = -1;

    for (i = 0; i < PARAM_P; ++i) {
        small i1 = in[i] & 1;
        g[PARAM_P - 1 - i] = (small)(i1 - (in[i] & (i1 << 1)));
    }
    g[PARAM_P] = 0;

    delta = 1;

    for (loop = 0; loop < 2 * PARAM_P - 1; ++loop) {
        for (i = PARAM_P; i > 0; --i)
            v[i] = v[i - 1];
        v[0] = 0;

        sign = -g[0] * f[0];
        swap = int16_negative_mask(-delta) & int16_nonzero_mask(g[0]);
        delta ^= swap & (delta ^ -delta);
        delta++;

        for (i = 0; i < PARAM_P + 1; ++i) {
            t = swap & (f[i] ^ g[i]);
            f[i] ^= (small)t;
            g[i] ^= (small)t;
            t = swap & (v[i] ^ r[i]);
            v[i] ^= (small)t;
            r[i] ^= (small)t;
        }

        for (i = 0; i < PARAM_P + 1; ++i)
            g[i] = F3_freeze((int16_t)(g[i] + sign * f[i]));

        for (i = 0; i < PARAM_P + 1; ++i)
            r[i] = F3_freeze((int16_t)(r[i] + sign * v[i]));

        for (i = 0; i < PARAM_P; ++i)
            g[i] = g[i + 1];

        g[PARAM_P] = 0;
    }

    sign = (int)f[0];
    for (i = 0; i < PARAM_P; ++i)
        out[i] = (small)(sign * v[PARAM_P - 1 - i]);

    out[PARAM_P] = (small)int16_nonzero_mask(delta);
    return 0;
}
