#ifndef OFF_HELPER_H_INCLUDED
#define OFF_HELPER_H_INCLUDED

#include <freeglut.h>
#include "vectors.h"
#include "off.h"

void Off_draw(Off const * off);

vec Off_center(Off const * off);

double Off_bsphere_rad(Off const * off, vec const * c);

void Off_normalize(Off * off);

#endif // GLUTHELP_H_INCLUDED
