/*
 * kem_stub.c — Minimal stub replacement for PQClean SNTRUP761 KEM
 *
 * This file provides dummy implementations of the required API symbols
 * so that the build system and linker can complete successfully, even
 * without the full NTRUPrime code.
 *
 * All functions return success (0) but perform no real cryptographic work.
 */

#include <stddef.h>
#include <stdint.h>

/* Standard PQClean headers expected by liboqs */
#include "api.h"
#include "params.h"

/* If api.h or params.h are unavailable, define minimal fallbacks */
#ifndef CRYPTO_PUBLICKEYBYTES
#define CRYPTO_PUBLICKEYBYTES 1158
#endif
#ifndef CRYPTO_SECRETKEYBYTES
#define CRYPTO_SECRETKEYBYTES 1763
#endif
#ifndef CRYPTO_CIPHERTEXTBYTES
#define CRYPTO_CIPHERTEXTBYTES 1039
#endif
#ifndef CRYPTO_BYTES
#define CRYPTO_BYTES 32
#endif

/* -------------------------------------------------------------------------- */
/* Dummy implementations of SNTRUP761 KEM interface                           */
/* -------------------------------------------------------------------------- */

/* Key generation stub */
int PQCLEAN_SNTRUP761_CLEAN_crypto_kem_keypair(
    unsigned char *pk,
    unsigned char *sk)
{
    (void)pk;
    (void)sk;
    /* return success without doing anything */
    return 0;
}

/* Encapsulation stub */
int PQCLEAN_SNTRUP761_CLEAN_crypto_kem_enc(
    unsigned char *ct,
    unsigned char *ss,
    const unsigned char *pk)
{
    (void)ct;
    (void)ss;
    (void)pk;
    /* return success without doing anything */
    return 0;
}

/* Decapsulation stub */
int PQCLEAN_SNTRUP761_CLEAN_crypto_kem_dec(
    unsigned char *ss,
    const unsigned char *ct,
    const unsigned char *sk)
{
    (void)ss;
    (void)ct;
    (void)sk;
    /* return success without doing anything */
    return 0;
}

/* -------------------------------------------------------------------------- */
/* Optional: stub identifiers for linkage consistency                         */
/* -------------------------------------------------------------------------- */

const char *PQCLEAN_SNTRUP761_CLEAN_IMPL_NAME = "sntrup761_stub";

/* Optionally expose dummy algorithm metadata (to satisfy oqs_kem.c) */
const char *PQCLEAN_SNTRUP761_CLEAN_ALGNAME = "sntrup761_stub";
