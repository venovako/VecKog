/* number of vectors in a 4k-page */
#ifdef V_PG
#error V_PG already defined
#else /* !V_PG */
#define V_PG 64u
#endif /* ?V_PG */

static inline size_t n2pg(const size_t n)
{
  return ((n + 511u) >> 9u);
}

static void zero_pgs(const size_t pg, double d[static 1])
{
  const unsigned
    nt = (unsigned)omp_get_num_threads(),
    ix = (unsigned)omp_get_thread_num();
  const size_t
    q = pg / nt;
  const unsigned
    r = (unsigned)(pg % nt);
  size_t n, b;
  if (r) {
    if (ix < r) {
      n = q + 1u;
      b = ix * n;
    }
    else {
      n = q;
      b = ix * n + r;
    }
  }
  else {
    n = q;
    b = ix * n;
  }
  const size_t
    e = b + n;
  register const VD z = VI(setzero)();
  for (size_t j = b; j < e; ++j) {
    double *const p = d + (j << 9u);
    for (size_t i = (size_t)0u; i < (size_t)V_PG; ++i) {
      double *const v = p + (i << VLlg);
      VI(stream)(v, z);
    }
  }
}

double *Valloc(const size_t n)
{
  const size_t pg = n2pg(n);
  double *const d = (double*)(pg ? aligned_alloc(4096u, (pg << 12u)) : NULL);
  if (d) {
    /* each thread zeroes-out its portion of the pages of *d */
#pragma omp parallel default(none) shared(pg,d)
    zero_pgs(pg, d);
  }
  else {
    perror("aligned_alloc");
    if (n)
      exit(EXIT_FAILURE);
  }
  return d;
}
