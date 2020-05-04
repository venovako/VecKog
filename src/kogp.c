  // constants
  register const VD m0 = VI(set1)(-0.0); VP(m0);
  register const VD p0 = VI(setzero)(); VP(p0);
  register const VD p1 = VI(set1)(+1.0); VP(p1);
  register const VD m = VI(set1)(DBL_TRUE_MIN); VP(m);
  register const VD h = VI(set1)((double)(DBL_MAX_EXP - 3)); VP(h);
  register const VD twof = VI(set1)((double)(1ull << (DBL_MANT_DIG + 1))); VP(twof);
