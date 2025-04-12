#pragma once

#include "pgconfig.h"
#include "pggraphics.h"
#include "pgtypes.h"
#include "pgutils.h"
#include <math.h>
#include <pspctrl.h>
#include <pspkernel.h>

GameState initGame();
void gameLoop(GameState *gs);
void cleanupGame();