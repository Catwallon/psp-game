#include "input.h"

void initInput() {
  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

void handleInput(GameState *gs) { sceCtrlReadBufferPositive(&gs->pad, 1); }

int isPressed(GameState *gs, enum PspCtrlButtons button) {
  return gs->pad.Buttons & button;
}