#pragma once

#include "config.h"
#include "gamestate.h"
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

typedef struct {
  float x, y, z;
} Vertex;

void initGu();
void renderGame(GameState *gs);
void cleanupGu();
