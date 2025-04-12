#pragma once

#define M_PI 3.14159265358979323846

#include "pgtypes.h"
#include <math.h>

// radian.c
float degToRad(float deg);
float radToDeg(float rad);

// simplex.c
float simplex2D(fVec2 coord);

// vector.c
fVec3 crossVec3(fVec3 a, fVec3 b);
fVec3 normalizeVec3(fVec3 v);
