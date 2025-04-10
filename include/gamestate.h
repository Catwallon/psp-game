#pragma once

#include "texture.h"
#include "types.h"
#include <pspctrl.h>
#include <pspkernel.h>

typedef struct {
  ScePspFVector3 playerPos;
  ScePspFVector3 playerRot;
  Vector2 chunk;
  SceCtrlData pad;
  SceCtrlData previousPad;
  unsigned long long tick;
  unsigned long long previousTick;
  char debug;
  TextureCache textureCache;
} GameState;