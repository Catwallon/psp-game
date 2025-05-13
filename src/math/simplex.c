#include "pgmath.h"
#define FNL_IMPL
#include "fastnoiselite.h"

float simplex2D(fVec2 pos) {
  static fnl_state state;
  static char init = false;

  if (!init) {
    state = fnlCreateState();
    state.noise_type = FNL_NOISE_OPENSIMPLEX2;
    state.frequency = 0.005;
    state.fractal_type = FNL_FRACTAL_RIDGED;
    init = true;
  }

  float y = fnlGetNoise2D(&state, pos.x, pos.y) * 10;
  return y;
}