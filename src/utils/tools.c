#include "pgutils.h"

float getDeltaTime(GameState *gs) {
  unsigned int resolution = sceRtcGetTickResolution();
  unsigned long long tickDiff = gs->tick - gs->previousTick;

  return (float)tickDiff / resolution;
}

unsigned int getFPS(GameState *gs) {
  float fps = 1 / getDeltaTime(gs);

  return (unsigned int)(fps + 0.5f);
}