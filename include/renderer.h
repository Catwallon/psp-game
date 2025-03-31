#pragma once

#include "chunk.h"
#include "config.h"
#include "gamestate.h"
#include "tools.h"
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

void initGu();
void renderGame(GameState *gs);
void cleanupGu();
