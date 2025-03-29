#pragma once

#include "gamestate.h"
#include <pspctrl.h>

void initInput();

void handleInput(GameState *gs);

int isPressed(GameState *gs, enum PspCtrlButtons button);