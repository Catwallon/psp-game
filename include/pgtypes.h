#pragma once

#include "pgconfig.h"
#include "pgconst.h"
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
  iVec2 pos;
  int size;
  char generated;
} Chunk;

typedef struct {
  Chunk chunks[NB_CHUNKS];
  unsigned int index;
} ChunkQueue;

typedef struct {
  void *vBuffer;
  unsigned int vCount;
  int vType;
  ChunkQueue chunkQueue;
  Texture texture;
} Terrain;

typedef struct {
  unsigned int fbp0Addr;
  unsigned int fbp1Addr;
  unsigned int currentBuffer;
  fVec3 playerPos;
  fVec3 playerRot;
  iVec2 chunk;
  SceCtrlData pad;
  SceCtrlData previousPad;
  TextureCache textureCache;
  Terrain terrain;
  unsigned long long tick;
  unsigned long long previousTick;
  char debug;
} GameState;
