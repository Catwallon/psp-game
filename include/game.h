#pragma once

#include "config.h"
#include "gamestate.h"
#include "input.h"
#include "renderer.h"
#include <pspctrl.h>
#include <pspkernel.h>

GameState initGame();
void gameLoop(GameState *gs);
void cleanupGame();