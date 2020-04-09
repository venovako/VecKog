#ifndef COMMON_H
#define COMMON_H

#ifdef __ICC
#include <mathimf.h>
extern __float128 __fmaq(__float128, __float128, __float128);
extern __float128 __fmaxq(__float128, __float128);
extern __float128 __hypotq(__float128, __float128);
#else /* !__ICC */
#include <complex.h>
#include <math.h>
#ifndef USE_EXTENDED
#define USE_EXTENDED
#endif /* !USE_EXTENDED */
#endif /* __ICC */

#ifdef USE_EXTENDED
typedef long double wide;
#ifndef fmaw
#define fmaw fmal
#else /* fmaw */
#error fmaw already defined
#endif /* ?fmaw */
#ifndef fmaxw
#define fmaxw fmaxl
#else /* fmaxw */
#error fmaxw already defined
#endif /* ?fmaxw */
#ifndef hypotw
#define hypotw hypotl
#else /* hypotw */
#error hypotw already defined
#endif /* ?hypotw */
#else /* USE_QUAD */
typedef __float128 wide;
#ifndef fmaw
#define fmaw __fmaq
#else /* fmaw */
#error fmaw already defined
#endif /* ?fmaw */
#ifndef fmaxw
#define fmaxw __fmaxq
#else /* fmaxw */
#error fmaxw already defined
#endif /* ?fmaxw */
#ifndef hypotw
#define hypotw __hypotq
#else /* hypotw */
#error hypotw already defined
#endif /* ?hypotw */
#endif /* ?USE_EXTENDED */

#ifndef CMPLXF
#define CMPLXF(r,i) ((float)(r) + I * (float)(i))
#endif /* !CMPLXF */
#ifndef CMPLX
#define CMPLX(r,i) ((double)(r) + I * (double)(i))
#endif /* !CMPLX */
#ifndef CMPLXL
#define CMPLXL(r,i) ((long double)(r) + I * (long double)(i))
#endif /* !CMPLXL */

#ifndef CMPLXW
#define CMPLXW(r,i) ((wide)(r) + I * (wide)(i))
#else /* CMPLXW */
#error CMPLXW already defined
#endif /* ?CMPLXW */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <limits.h>
#include <signal.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef FINT64
typedef int64_t fint;
typedef uint64_t fnat;
#ifndef FINT_C
#define FINT_C(x) INT64_C(x)
#else /* FINT_C */
#error FINT_C already defined
#endif /* ?FINT_C */
#ifndef FNAT_C
#define FNAT_C(x) UINT64_C(x)
#else /* FNAT_C */
#error FNAT_C already defined
#endif /* ?FNAT_C */
#else /* FINT32 */
typedef int32_t fint;
typedef uint32_t fnat;
#ifndef FINT_C
#define FINT_C(x) INT32_C(x)
#else /* FINT_C */
#error FINT_C already defined
#endif /* ?FINT_C */
#ifndef FNAT_C
#define FNAT_C(x) UINT32_C(x)
#else /* FNAT_C */
#error FNAT_C already defined
#endif /* ?FNAT_C */
#endif /* ?FINT64 */

#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef USE_MKL
#ifdef FINT64
#ifndef MKL_ILP64
#define MKL_ILP64
#endif /* !MKL_ILP64 */
#endif /* FINT64 */
#ifndef MKL_Complex8
#define MKL_Complex8 float _Complex
#endif /* !MKL_Complex8 */
#ifndef MKL_Complex16
#define MKL_Complex16 double _Complex
#endif /* !MKL_Complex16 */
#include <mkl.h>
#ifndef BLAS_S
#define BLAS_S(name) s##name
#endif /* !BLAS_S */
#ifndef BLAS_D
#define BLAS_D(name) d##name
#endif /* !BLAS_D */
#ifndef BLAS_C
#define BLAS_C(name) c##name
#endif /* !BLAS_C */
#ifndef BLAS_Z
#define BLAS_Z(name) z##name
#endif /* !BLAS_Z */
#else /* some other Fortran-compatible BLAS */
#ifndef BLAS_S
#define BLAS_S(name) s##name##_
#endif /* !BLAS_S */
#ifndef BLAS_D
#define BLAS_D(name) d##name##_
#endif /* !BLAS_D */
#ifndef BLAS_C
#define BLAS_C(name) c##name##_
#endif /* !BLAS_C */
#ifndef BLAS_Z
#define BLAS_Z(name) z##name##_
#endif /* !BLAS_Z */
#endif /* ?USE_MKL */

#ifndef LAPACK_S
#define LAPACK_S(name) s##name##_
#endif /* !LAPACK_S */
#ifndef LAPACK_D
#define LAPACK_D(name) d##name##_
#endif /* !LAPACK_D */
#ifndef LAPACK_C
#define LAPACK_C(name) c##name##_
#endif /* !LAPACK_C */
#ifndef LAPACK_Z
#define LAPACK_Z(name) z##name##_
#endif /* !LAPACK_Z */

extern size_t atoz(const char *const s);

#endif /* !COMMON_H */
