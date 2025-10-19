#include <stdint.h>
#include <stddef.h>
#include "crypto_core_inv3sntrup761.h"
#include "params.h"

/* avoid name collision with stdio.h 'p' variables */
#ifndef PARAM_P
#define PARAM_P 761
#endif

#define int8 int8_t
#define int16 int16_t
#define int32 int32_t
#define uint16 uint16_t
#define uint32 uint32_t

/* ----- masks */

/* return -1 if x!=0; else return 0 */
static int int16_nonzero_mask(int16 x) {
    uint16 u = (uint16)x;
    uint32 v = u;
    v = ~v + 1;
    v >>= 31;
    return -(int)v;
}

/* return -1 if x<0; otherwise return 0 */
static int int16_negative_mask(int16 x) {
    uint16 u = (uint16)x;
    u >>= 15;
    return -(int)u;
}

/* ----- arithmetic mod 3 */

typedef int8 small;

/* works for -16384 <= x < 16384 */
static small F3_freeze(int16 x) {
    return (small)(x - 3 * ((10923 * x + 16384) >> 15));
}

/* byte PARAM_P of output is 0 if recip succeeded; else -1 */
int PQCLEAN_SNTRUP761_CLEAN_crypto_core_inv3sntrup761(
    unsigned char *outbytes,
    const unsigned char *inbytes) {

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

    for (i = 0; i < PARAM_P; ++i)
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
        swap = int16_negative_mask((int16)-delta) & int16_nonzero_mask(g[0]);
        delta ^= swap & (delta ^ -delta);
        delta += 1;

        for (i = 0; i < PARAM_P + 1; ++i) {
            t = swap & (f[i] ^ g[i]);
            f[i] ^= (small)t;
            g[i] ^= (small)t;
            t = swap & (v[i] ^ r[i]);
            v[i] ^= (small)t;
            r[i] ^= (small)t;
        }

        for (i = 0; i < PARAM_P + 1; ++i)
            g[i] = F3_freeze((int16)(g[i] + sign * f[i]));
        for (i = 0; i < PARAM_P + 1; ++i)
            r[i] = F3_freeze((int16)(r[i] + sign * v[i]));

        for (i = 0; i < PARAM_P; ++i)
            g[i] = g[i + 1];
        g[PARAM_P] = 0;
    }

    sign = (int)f[0];
    for (i = 0; i < PARAM_P; ++i)
        out[i] = (small)(sign * v[PARAM_P - 1 - i]);

    out[PARAM_P] = (small)int16_nonzero_mask((int16)delta);
    return 0;
}
