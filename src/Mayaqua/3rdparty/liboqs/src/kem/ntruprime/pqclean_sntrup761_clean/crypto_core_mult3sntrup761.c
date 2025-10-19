#include <stdint.h>
#include <stddef.h>
#include "global_clean.h"
#include "crypto_core_mult3sntrup761.h"

/*
 * Multiply two polynomials with coefficients in {-1, 0, 1}
 * modulo (x^p - x - 1), reducing all coefficients mod 3.
 * Input:  inbytes -> small coefficients (-1, 0, 1)
 *         kbytes  -> small coefficients (-1, 0, 1)
 * Output: outbytes -> small coefficients (-1, 0, 1)
 */

int PQCLEAN_SNTRUP761_CLEAN_crypto_core_mult3sntrup761(
    unsigned char *outbytes,
    const unsigned char *inbytes,
    const unsigned char *kbytes)
{
    small f[PARAM_P];
    small g[PARAM_P];
    small fg[PARAM_P + PARAM_P - 1];
    int32_t acc;
    int i, j;

    /* Decode inputs (bytes to small) */
    for (i = 0; i < PARAM_P; ++i) {
        f[i] = (small)inbytes[i];
    }

    for (i = 0; i < PARAM_P; ++i) {
        g[i] = (small)kbytes[i];
    }

    /* Schoolbook polynomial multiplication */
    for (i = 0; i < PARAM_P; ++i) {
        acc = 0;
        for (j = 0; j <= i; ++j) {
            acc += (int32_t)f[j] * (int32_t)g[i - j];
        }
        fg[i] = F3_freeze(acc);
    }

    for (i = PARAM_P; i < PARAM_P + PARAM_P - 1; ++i) {
        acc = 0;
        for (j = i - PARAM_P + 1; j < PARAM_P; ++j) {
            acc += (int32_t)f[j] * (int32_t)g[i - j];
        }
        fg[i] = F3_freeze(acc);
    }

    /* Modular reduction mod (x^p - x - 1) */
    for (i = PARAM_P + PARAM_P - 2; i >= PARAM_P; --i) {
        fg[i - PARAM_P]     = F3_freeze((int16_t)fg[i - PARAM_P]     + (int16_t)fg[i]);
        fg[i - PARAM_P + 1] = F3_freeze((int16_t)fg[i - PARAM_P + 1] + (int16_t)fg[i]);
    }

    /* Encode output */
    for (i = 0; i < PARAM_P; ++i) {
        outbytes[i] = (unsigned char)fg[i];
    }

    return 0;
}
