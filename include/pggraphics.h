#pragma once

#include "pgconfig.h"
#include "pgmath.h"
#include "pgtypes.h"
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <stdlib.h>

// texture.c
extern unsigned char grass_start[];
TextureCache initTextureCache();

// render.c
void initGu();
void renderGame(GameState *gs);
void cleanupGu();

// terrain.c
Terrain initTerrain(GameState *gs);
void updateChunkQueue(GameState *gs);
void generateChunk(GameState *gs);