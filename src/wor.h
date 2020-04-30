#ifndef WOR_H
#define WOR_H

#include "common.h"

/* Computes || U^T U - I ||_F in wide precision. */
extern wide wdor
(const double u11, const double u21, const double u12, const double u22);

/* Computes || U^H U - I ||_F in wide precision. */
extern wide wzor
(const double u11r, const double u11i, const double u21r, const double u21i,
 const double u12r, const double u12i, const double u22r, const double u22i);

#endif /* !WOR_H */
