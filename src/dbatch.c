#include "kog.h"
#include "mem.h"
#ifdef USE_MSR
#include "msr.h"
#endif /* USE_MSR */
#include "wre.h"

int main(int argc, char *argv[])
{
  if (4 != argc) {
    (void)fprintf(stderr, "%s n #batches infile\n", argv[0]);
    return EXIT_FAILURE;
  }
  const size_t n = atoz(argv[1]);
  if (!n) {
    perror("atoz(n)");
    return EXIT_FAILURE;
  }
  // TODO: FIXME for n not a power of two
  if (_mm_popcnt_u64(n) > (__int64)1) {
    perror("n not a power of two");
    return EXIT_FAILURE;
  }
  const size_t b = atoz(argv[2]);
  if (!b) {
    perror("atoz(b)");
    return EXIT_FAILURE;
  }
  FILE *const f = fopen(argv[3], "rb");
  if (!f) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  Dmem *const d = Dalloc(n);
  if (!d)
    return EXIT_FAILURE;
  Tout *const t = Talloc(n);
  if (!t)
    return EXIT_FAILURE;

  (void)fprintf(stdout, "\"DBATCH\",\"WTIMEs\",\"K2\",\"RE\",\"OU\",\"OV\"");
#ifdef USE_MSR
  (void)fprintf(stdout, ",\"A_M\"");
#endif /* USE_MSR */
  (void)fprintf(stdout, "\n");
  (void)fflush(stdout);
  const size_t V = n2V(n);

#ifdef USE_MSR
  const size_t mt = (size_t)omp_get_max_threads();
  FILE *const mf = fopen("dmsr.csv", "w");
  if (!mf) {
    perror("fopen(dmsr.csv)");
    return EXIT_FAILURE;
  }
  (void)fprintf(mf, "\"DBATCH\",\"TIX\",\"MPERF\",\"APERF\"\n");
  (void)fflush(mf);
#endif /* USE_MSR */

  for (size_t j = (size_t)1u; j <= b; ++j) {
    if (n != fread(d->r.A11, sizeof(double), n, f)) {
      perror("fread(A11r)");
      return EXIT_FAILURE;
    }
    if (n != fread(d->r.A21, sizeof(double), n, f)) {
      perror("fread(A21r)");
      return EXIT_FAILURE;
    }
    if (n != fread(d->r.A12, sizeof(double), n, f)) {
      perror("fread(A12r)");
      return EXIT_FAILURE;
    }
    if (n != fread(d->r.A22, sizeof(double), n, f)) {
      perror("fread(A22r)");
      return EXIT_FAILURE;
    }

    double
#ifdef USE_MSR
      avg = 0.0,
#endif /* USE_MSR */
      w = omp_get_wtime();
#ifdef _OPENMP
#ifdef USE_MSR
#pragma omp parallel default(none) shared(j,V,d,mf) reduction(+:avg)
#else /* !USE_MSR */
#pragma omp parallel default(none) shared(V,d)
#endif /* ?USE_MSR */
    {
#endif /* _OPENMP */
#ifdef USE_MSR
      const int tix = omp_get_thread_num();
      const int cfd = msr_open(msr_mycpu());
      uint64_t aperf = UINT64_C(0), mperf = UINT64_C(0);
      if (cfd >= 0) {
        (void)msr_read(cfd, IA32_MPERF, &mperf);
        (void)msr_read(cfd, IA32_APERF, &aperf);
      }
#endif /* USE_MSR */
#ifdef _OPENMP
#pragma omp for
#endif /* _OPENMP */
      for (size_t i = (size_t)0u; i < V; ++i) {
        const size_t k = (i << VLlg);
        d8svd2_
          ((d->r.A11 + k), (d->r.A21 + k), (d->r.A12 + k), (d->r.A22 + k),
           (d->r.U11 + k), (d->r.U21 + k), (d->r.U12 + k), (d->r.U22 + k),
           (d->r.V11 + k), (d->r.V21 + k), (d->r.V12 + k), (d->r.V22 + k),
           (d->v.S1 + k), (d->v.S2 + k), (d->v.s + k));
      }
#ifdef USE_MSR
      if (cfd >= 0) {
        uint64_t mval = UINT64_C(0), aval = UINT64_C(0);
        (void)msr_read(cfd, IA32_MPERF, &mval);
        (void)msr_read(cfd, IA32_APERF, &aval);
        (void)msr_close(cfd);
        mperf = ((mval > mperf) ? (mval - mperf) : UINT64_C(0));
        aperf = ((aval > aperf) ? (aval - aperf) : UINT64_C(0));
        avg = ((mperf && aperf && (mperf > aperf)) ? (((double)aperf) / mperf) : 1.0);
      }
      else
        avg = 1.0;
#pragma omp critical
      {
        (void)fprintf(mf, "%zu,%d,%lu,%lu\n", j, tix, mperf, aperf);
        (void)fflush(mf);
      }
#endif /* USE_MSR */
#ifdef _OPENMP
    }
#endif /* _OPENMP */
    w = omp_get_wtime() - w;
#ifdef USE_MSR
    avg /= mt;
#endif /* USE_MSR */

    wdre
      (n, t->K2, t->RE, t->OU, t->OV,
       d->r.A11, d->r.A21, d->r.A12, d->r.A22,
       d->r.U11, d->r.U21, d->r.U12, d->r.U22,
       d->r.V11, d->r.V21, d->r.V12, d->r.V22,
       d->v.S1, d->v.S2, d->v.s);
    // TODO: FIXME for n not a power of two
    for (size_t k = n >> 1u; k; k >>= 1u) {
#ifdef _OPENMP
#pragma omp parallel for default(none) shared(k,t)
#endif /* _OPENMP */
      for (size_t i = (size_t)0u; i < k; ++i) {
        (t->K2)[i] = fmaxw((t->K2)[i], (t->K2)[i + k]);
        (t->RE)[i] = fmaxw((t->RE)[i], (t->RE)[i + k]);
        (t->OU)[i] = fmaxw((t->OU)[i], (t->OU)[i + k]);
        (t->OV)[i] = fmaxw((t->OV)[i], (t->OV)[i + k]);
      }
    }
    (void)Bwre(stdout, j, w, *(t->K2), *(t->RE), *(t->OU), *(t->OV),
#ifdef USE_MSR
               &avg
#else /* !USE_MSR */
               (const double*)NULL
#endif /* ?USE_MSR */
               );
  }

#ifdef USE_MSR
  (void)fclose(mf);
#endif /* USE_MSR */
  (void)Tfree(t);
  (void)Dfree(d);
  return (fclose(f) ? EXIT_FAILURE : EXIT_SUCCESS);
}
