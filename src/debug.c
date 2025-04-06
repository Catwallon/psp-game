#include "debug.h"

void initDebug() { pspDebugScreenInit(); }

void displayDebug(GameState *gs) {
  pspDebugScreenSetXY(0, 0);
  pspDebugScreenPrintf("Pos XYZ: %.3f / %.3f / %.3f\n", gs->playerPos.x,
                       gs->playerPos.y, gs->playerPos.z);
  pspDebugScreenPrintf("Rot XYZ: %.3f / %.3f / %.3f\n",
                       radToDeg(gs->playerRot.x), radToDeg(gs->playerRot.y),
                       radToDeg(gs->playerRot.z));
  pspDebugScreenPrintf("FPS: %d\n", getFPS(gs));
}

void printDebug(GameState *gs) {
  fprintf(stdout, "Pos XYZ: %.3f / %.3f / %.3f\n", gs->playerPos.x,
          gs->playerPos.y, gs->playerPos.z);
  fprintf(stdout, "Rot XYZ: %.3f / %.3f / %.3f\n", radToDeg(gs->playerRot.x),
          radToDeg(gs->playerRot.y), radToDeg(gs->playerRot.z));
  fprintf(stdout, "Chunk XY: %d / %d\n", gs->chunk.x, gs->chunk.y);
  fprintf(stdout, "FPS: %d\n", getFPS(gs));
}