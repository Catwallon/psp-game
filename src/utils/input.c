#include "pgutils.h"

void initInput() {
  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

void handleInput(GameState *gs) {
  gs->previousPad = gs->pad;
  sceCtrlReadBufferPositive(&gs->pad, 1);
}

char isPressed(GameState *gs, enum PspCtrlButtons button) {
  if (gs->pad.Buttons & button)
    return 1;
  return 0;
}

char isJustPressed(GameState *gs, enum PspCtrlButtons button) {
  if (!(gs->previousPad.Buttons & button) && isPressed(gs, button))
    return 1;
  return 0;
}

unsigned char getAnalogX(GameState *gs) { return gs->pad.Lx; }

unsigned char getAnalogY(GameState *gs) { return gs->pad.Ly; }