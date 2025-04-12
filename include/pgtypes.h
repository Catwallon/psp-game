#pragma once

#include "pgconfig.h"
#include <pspctrl.h>
#include <psptypes.h>

typedef struct ScePspIVector2 iVec2;
typedef struct ScePspIVector3 iVec3;
typedef struct ScePspFVector2 fVec2;
typedef struct ScePspFVector3 fVec3;

typedef struct {
  int width;
  int height;
  unsigned char *data;
} Texture;

typedef struct {
  Texture grass;
} TextureCache;

typedef struct {
  void *buffer;
  unsigned int size;
  int type;
  Texture texture;
} Model;

typedef struct {
  Model terrain;
} ModelCache;

typedef struct {
  Model models[MAX_DRAW_CALL];
  unsigned int index;
} DrawList;

typedef struct {
  fVec3 playerPos;
  fVec3 playerRot;
  iVec2 chunk;
  SceCtrlData pad;
  SceCtrlData previousPad;
  TextureCache textureCache;
  ModelCache modelCache;
  DrawList drawList;
  unsigned long long tick;
  unsigned long long previousTick;
  char debug;
} GameState;
