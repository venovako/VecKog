  // constants
  register const VD m0 = VI(set1)(-0.0); VP(m0);
  register const VD p0 = VI(setzero)(); VP(p0);
  register const VD p1 = VI(set1)(+1.0); VP(p1);
  register const VD m = VI(set1)(DBL_TRUE_MIN); VP(m);
  // (double)(DBL_MAX_EXP - 3)
  register const VD h = VI(set1)(1021.0); VP(h);
  // sqrt(DBL_MAX)
  register const VD twof = VI(set1)(1.34078079299425956E+154); VP(twof);
