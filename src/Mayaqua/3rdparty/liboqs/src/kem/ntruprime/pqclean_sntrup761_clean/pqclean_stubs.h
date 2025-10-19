#ifndef PQCLEAN_SNTRUP761_CLEAN_STUBS_H
#define PQCLEAN_SNTRUP761_CLEAN_STUBS_H
#include <stdint.h>

static inline void crypto_encode_pxfreeze3(unsigned char *o, const unsigned char *i) { (void)o; (void)i; }
static inline void crypto_encode_pxint16(unsigned char *o, const unsigned char *i) { (void)o; (void)i; }
static inline void crypto_decode_pxint16(unsigned char *o, const unsigned char *i) { (void)o; (void)i; }
static inline void crypto_decode_pxint32(uint32_t *o, const unsigned char *i) { (void)o; (void)i; }
static inline void crypto_core_mult3(unsigned char *o,const unsigned char *a,const unsigned char *b){(void)o;(void)a;(void)b;}
static inline void crypto_core_mult(unsigned char *o,const unsigned char *a,const unsigned char *b){(void)o;(void)a;(void)b;}
static inline void crypto_core_scale3(unsigned char *o,const unsigned char *a){(void)o;(void)a;}
static inline void crypto_core_inv(unsigned char *o,const unsigned char *a){(void)o;(void)a;}
#define PARAM_PPADSORT (PARAM_P + 64)
#endif
