#pragma once

#include "pgconfig.h"
#include "pgmath.h"
#include "pgtypes.h"
#include "pgutils.h"
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <stdio.h>
#include <stdlib.h>

// texture.c
Texture loadTexture(char *path, unsigned int width, unsigned int height,
                    int type);

// render.c
void initGu(GameState *gs);
void renderGame(GameState *gs);
void cleanupGu();

// terrain.c
Terrain initTerrain(GameState *gs);
void updateChunkQueue(GameState *gs);
void generateChunk(GameState *gs);

// model.c
ModelCache initModelCache();