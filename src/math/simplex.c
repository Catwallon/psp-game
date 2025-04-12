#include "pgmath.h"

// TODO: Simplex noise
float simplex2D(fVec2 pos) {
  return sinf(pos.x * 0.01f) * cosf(pos.y * 0.01) * 50;
}