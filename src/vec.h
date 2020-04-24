#ifndef VEC_H
#define VEC_H

#include "common.h"

#ifdef __AVX512F__
#include <immintrin.h>
#else /* !__AVX512F__ */
#error AVX-512 instructions not available
#endif /* ?__AVX512F__ */

/*** redefine if changing the vector type ***/

/* vector type containing doubles */
#ifdef VD
#error VD already defined
#else /* !VD */
#define VD __m512d
#endif /* ?VD */

/* vector length in 64-bit lanes */
#ifdef VL
#error VL already defined
#else /* !VL */
#define VL 8u
#endif /* ?VL */

/* VL - 1 */
#ifdef VL_1
#error VL_1 already defined
#else /* !VL_1 */
#define VL_1 7u
#endif /* ?VL_1 */

/* lg(VL) */
#ifdef VLlg
#error VLlg already defined
#else /* !VLlg */
#define VLlg 3u
#endif /* ?VLlg */

/* alignment of VD in bytes */
#ifdef VA
#error VA already defined
#else /* !VA */
#define VA 64u
#endif /* ?VA */

/* vector instruction name */
#ifdef VI
#error VI already defined
#else /* !VI */
#define VI(x) _mm512_##x##_pd
#endif /* ?VI */

/*** end of vector definitions ***/

static inline size_t n2V(const size_t n)
{
  return ((n + VL_1) >> VLlg);
}

static inline size_t n2N(const size_t n)
{
  return (n2V(n) << VLlg);
}

#endif /* !VEC_H */
