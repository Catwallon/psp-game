#pragma once

#include "gamestate.h"
#include <pspctrl.h>

void initInput();
void handleInput(GameState *gs);
char isPressed(GameState *gs, enum PspCtrlButtons button);
char isJustPressed(GameState *gs, enum PspCtrlButtons button);
unsigned char getAnalogX(GameState *gs);
unsigned char getAnalogY(GameState *gs);