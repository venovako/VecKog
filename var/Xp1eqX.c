#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  const int f = DBL_MANT_DIG + 1;
  const double x = scalbn(1.0, f);
  (void)printf("f=%d, (x==(x+1))=%d\n", DBL_MANT_DIG, (int)(x == (x + 1.0)));
  (void)printf("hypot(DBL_MAX,1)=%#.17e\n", hypot(DBL_MAX, 1.0));
  const double z = sqrt(DBL_MAX);
  const double y = fma(z, z, 1.0);
  (void)printf("sqrt(DBL_MAX)=%#.17e, fma(sqrt(DBL_MAX),sqrt(DBL_MAX),1)=%#.17e\n", z, y);
  const double d = 1.0 + sqrt(y);
  (void)printf("d=%#.17e\n", d);
  return EXIT_SUCCESS;
}
