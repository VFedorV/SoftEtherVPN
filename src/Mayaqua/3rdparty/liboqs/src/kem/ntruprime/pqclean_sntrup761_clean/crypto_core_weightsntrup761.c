#include <stdint.h>
#include <stddef.h>
#include "global_clean.h"
#include "crypto_core_weightsntrup761.h"
#include "crypto_encode_int16.h"

/*
 * Compute the weight (number of 1 bits in least significant bits of input)
 * for SNTRUP761.
 *
 * Input:  inbytes  — pointer to array of bytes representing small values
 * Output: outbytes — little-endian int16 weight
 */

int PQCLEAN_SNTRUP761_CLEAN_crypto_core_weightsntrup761(
    unsigned char *outbytes,
    const unsigned char *inbytes)
{
    const int8_t *in = (const int8_t *)inbytes;
    int16_t weight = 0;
    int i;

    /* Count how many entries have LSB = 1 */
    for (i = 0; i < PARAM_P; ++i) {
        weight += (in[i] & 1);
    }

    PQCLEAN_SNTRUP761_CLEAN_crypto_encode_int16(outbytes, &weight);
    return 0;
}
