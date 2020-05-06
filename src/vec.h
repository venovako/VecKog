#ifndef VEC_H
#define VEC_H

#include "common.h"

/*** redefine if changing the vector type ***/

#ifdef __AVX512F__
#include <immintrin.h>
#else /* !__AVX512F__ */
#error AVX-512 instructions not available
#endif /* ?__AVX512F__ */

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

/* mask type for double lanes */
#ifdef MD
#error MD already defined
#else /* !MD */
#define MD __mmask8
#endif /* ?MD */

/* vector instruction name */
#ifdef VI
#error VI already defined
#else /* !VI */
#define VI(x) _mm512_##x##_pd
#endif /* ?VI */

/* <-comparison */
#ifdef LT
#error LT already defined
#else /* !LT */
#define LT _mm512_cmplt_pd_mask
#endif /* ?LT */

#ifdef AND
#error AND already defined
#endif /* AND */

#ifdef ANDNOT
#error ANDNOT already defined
#endif /* ANDNOT */

#ifdef OR
#error OR already defined
#endif /* OR */

#ifdef XOR
#error XOR already defined
#endif /* XOR */

#ifdef M2U
#error M2U already defined
#endif /* M2U */

#ifdef __AVX512DQ__
#define AND(x,y) VI(and)((x), (y))
#define ANDNOT(x,y) VI(andnot)((x), (y))
#define OR(x,y) VI(or)((x), (y))
#define XOR(x,y) VI(xor)((x), (y))
#define M2U(m) _cvtmask8_u32(m)
#else /* AVX512F only */
#define AND(x,y) _mm512_castsi512_pd(_mm512_and_epi64(_mm512_castpd_si512(x), _mm512_castpd_si512(y)))
#define ANDNOT(x,y) _mm512_castsi512_pd(_mm512_andnot_epi64(_mm512_castpd_si512(x), _mm512_castpd_si512(y)))
#define OR(x,y) _mm512_castsi512_pd(_mm512_or_epi64(_mm512_castpd_si512(x), _mm512_castpd_si512(y)))
#define XOR(x,y) _mm512_castsi512_pd(_mm512_xor_epi64(_mm512_castpd_si512(x), _mm512_castpd_si512(y)))
#define M2U(m) _cvtmask16_u32((__mmask16)(m))
#endif /* __AVX512DQ__ */

/*** end of vector definitions ***/

static inline size_t n2V(const size_t n)
{
  return ((n + VL_1) >> VLlg);
}

static inline size_t n2N(const size_t n)
{
  return (n2V(n) << VLlg);
}

extern int Vprintf(FILE f[static 1], const char *const h, const VD v);

#ifdef VP
#error VP already defined
#else /* !VP */
#ifdef TEST
#if ((TEST == 0) || (TEST == 1))
#define VP(v) Vprintf(stderr, #v, (v))
#else /* TEST < 0 or TEST > 1 */
#define VP(v) TEST
#endif /* TEST ?in {0,1} */
#else /* !TEST */
#define VP(v) 0
#endif /* ?TEST */
#endif /* ?VP */

extern int Mprintf(FILE f[static 1], const char *const h, const MD m);

#ifdef MP
#error MP already defined
#else /* !MP */
#ifdef TEST
#if ((TEST == 0) || (TEST == 1))
#define MP(m) Mprintf(stderr, #m, (m))
#else /* TEST < 0 or TEST > 1 */
#define MP(m) TEST
#endif /* TEST ?in {0,1} */
#else /* !TEST */
#define MP(m) 0
#endif /* ?TEST */
#endif /* ?MP */

extern size_t Vread(double d[static VL], const size_t V, FILE f[static 1]);
extern size_t Vwrite(const double d[static VL], const size_t V, FILE f[static 1]);

#endif /* !VEC_H */
