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
  void *buffer;
  unsigned int width;
  unsigned int height;
  int type;
} Texture;

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
  float *vBuffer;
  unsigned int vCount;
  int vType;
  int prim;
  Texture texture;
} Model;

typedef struct {
  Model knight;
} ModelCache;

typedef struct {
  unsigned int fbp0Addr;
  unsigned int fbp1Addr;
  unsigned int currentBuffer;
  fVec3 playerPos;
  fVec3 playerRot;
  iVec2 chunk;
  SceCtrlData pad;
  SceCtrlData previousPad;
  ModelCache modelCache;
  Terrain terrain;
  unsigned long long tick;
  unsigned long long previousTick;
  char debug;
} GameState;
