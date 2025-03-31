#pragma once

#include "gamestate.h"
#include <pspkernel.h>
#include <psprtc.h>

#define M_PI 3.14159265358979323846

typedef struct {
  float x, y, z;
} Vertex;

Vertex createVertex(float x, float y, float z);
float degToRad(float deg);
float radToDeg(float rad);
float getDeltaTime(GameState *gs);
unsigned int getFPS(GameState *gs);