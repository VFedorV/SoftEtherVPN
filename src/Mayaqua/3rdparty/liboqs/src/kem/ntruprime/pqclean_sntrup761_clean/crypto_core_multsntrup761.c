#include <stdint.h>
#include <stddef.h>
#include "global_clean.h"
#include "crypto_core_multsntrup761.h"

/*
 * Multiply two polynomials modulo (x^p - x - 1) with coefficients
 * reduced modulo PARAM_Q = 4591.
 * Input:  inbytes -> Fq coefficients
 *         kbytes  -> small coefficients (-1, 0, 1)
 * Output: outbytes -> Fq coefficients (mod q)
 */

int PQCLEAN_SNTRUP761_CLEAN_crypto_core_multsntrup761(
    unsigned char *outbytes,
    const unsigned char *inbytes,
    const unsigned char *kbytes)
{
    Fq f[PARAM_P];
    small g[PARAM_P];
    Fq fg[PARAM_P + PARAM_P - 1];
    int32_t acc;
    int i, j;

    /* Decode inputs */
    for (i = 0; i < PARAM_P; ++i) {
        f[i] = (Fq)((int16_t)inbytes[i]);
    }

    for (i = 0; i < PARAM_P; ++i) {
        /* Decode {0,1,2} to {-1,0,1} for small coefficients */
        small gi = (small)kbytes[i];
        small gi0 = gi & 1;
        g[i] = (small)(gi0 - (gi & (gi0 << 1)));
    }

    /* Schoolbook multiplication */
    for (i = 0; i < PARAM_P; ++i) {
        acc = 0;
        for (j = 0; j <= i; ++j) {
            acc += (int32_t)f[j] * (int32_t)g[i - j];
        }
        fg[i] = Fq_freeze(acc);
    }

    for (i = PARAM_P; i < PARAM_P + PARAM_P - 1; ++i) {
        acc = 0;
        for (j = i - PARAM_P + 1; j < PARAM_P; ++j) {
            acc += (int32_t)f[j] * (int32_t)g[i - j];
        }
        fg[i] = Fq_freeze(acc);
    }

    /* Reduction modulo x^p - x - 1 */
    for (i = PARAM_P + PARAM_P - 2; i >= PARAM_P; --i) {
        fg[i - PARAM_P]     = Fq_freeze((int32_t)fg[i - PARAM_P]     + (int32_t)fg[i]);
        fg[i - PARAM_P + 1] = Fq_freeze((int32_t)fg[i - PARAM_P + 1] + (int32_t)fg[i]);
    }

    /* Output lowest p coefficients */
    for (i = 0; i < PARAM_P; ++i) {
        ((Fq *)outbytes)[i] = fg[i];
    }

    return 0;
}
