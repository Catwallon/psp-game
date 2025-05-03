#include "pgutils.h"

void initDebug() {
  pspDebugScreenInit();
  pspDebugScreenEnableBackColor(0);
}

void displayDebug(GameState *gs) {
  pspDebugScreenSetOffset((gs->currentBuffer == (unsigned int)gs->fbp0Addr)
                              ? (unsigned int)gs->fbp1Addr
                              : (unsigned int)gs->fbp0Addr);
  pspDebugScreenSetXY(1, 1);
  pspDebugScreenPrintf("Pos XYZ: %.3f / %.3f / %.3f\n", gs->playerPos.x,
                       gs->playerPos.y, gs->playerPos.z);
  pspDebugScreenSetXY(1, 2);
  pspDebugScreenPrintf("Rot XYZ: %.3f / %.3f / %.3f\n",
                       radToDeg(gs->playerRot.x), radToDeg(gs->playerRot.y),
                       radToDeg(gs->playerRot.z));
  pspDebugScreenSetXY(1, 3);
  pspDebugScreenPrintf("FPS: %d\n", getFPS(gs));
}

void printDebug(GameState *gs) {
  // Debug
}