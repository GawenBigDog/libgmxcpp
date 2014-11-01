
#ifndef UTILS_H
#define UTILS_H

#include "xdrfile.h"
#include "xdrfile_xtc.h"
#include <math.h>
#include <cmath>

void pbc(rvec a, matrix box);
void cross(rvec a, rvec b, rvec r);

#endif
