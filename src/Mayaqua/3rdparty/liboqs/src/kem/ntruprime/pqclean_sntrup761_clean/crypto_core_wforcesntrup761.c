#include <stdint.h>
#include <stddef.h>
#include "global_clean.h"
#include "crypto_core_wforcesntrup761.h"
//#include "crypto_decode_int16.h"
#include "crypto_encode_int16.h"

/*
 * Force a given small polynomial to have exact weight PARAM_W.
 *
 * Input:  inbytes  — bytes representing small coefficients (-1, 0, 1)
 * Output: outbytes — adjusted coefficients with exactly PARAM_W entries of 1.
 *
 * This ensures the output polynomial has Hamming weight PARAM_W,
 * as required for SNTRUP761 key generation.
 */

int PQCLEAN_SNTRUP761_CLEAN_crypto_core_wforcesntrup761(
    unsigned char *outbytes,
    const unsigned char *inbytes)
{
    int8_t *out = (int8_t *)outbytes;
    const int8_t *in = (const int8_t *)inbytes;
    int i, weight = 0;

    /* Copy input and count how many bits are set */
    for (i = 0; i < PARAM_P; ++i) {
        out[i] = in[i] & 1;
        weight += out[i];
    }

    /* Force exact weight = PARAM_W by flipping bits if needed */
    if (weight > PARAM_W) {
        for (i = PARAM_P - 1; i >= 0 && weight > PARAM_W; --i) {
            if (out[i]) {
                out[i] = 0;
                --weight;
            }
        }
    } else if (weight < PARAM_W) {
        for (i = 0; i < PARAM_P && weight < PARAM_W; ++i) {
            if (!out[i]) {
                out[i] = 1;
                ++weight;
            }
        }
    }

    /* Encode back as bytes */
    for (i = 0; i < PARAM_P; ++i) {
        outbytes[i] = (unsigned char)out[i];
    }

    return 0;
}
