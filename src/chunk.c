#include "chunk.h"
#include <stdio.h>

// TODO: Simplex noise
static float simplex2D(float x, float z) {
  return sinf(x * 0.1f) * cosf(z * 0.1f);
}

static Vertex createChunkVertice(ScePspFVector3 chunkPos, int x, int z) {
  return createVertex(x, z, x, simplex2D(chunkPos.x + x, chunkPos.z + z), z);
}

void drawChunk(GameState *gs, ScePspFVector3 pos, int chunkRes) {
  sceGumLoadIdentity();
  sceGumTranslate(&pos);
  sceGuFrontFace(GU_CCW);

  sceGuTexMode(GU_PSM_8888, 0, 0, 0);
  sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
  sceGuTexImage(0, gs->textureCache.grass.width, gs->textureCache.grass.height,
                gs->textureCache.grass.width, gs->textureCache.grass.data);
  sceGuTexFilter(GU_LINEAR, GU_LINEAR);
  sceGuTexWrap(GU_REPEAT, GU_REPEAT);

  int index = 0;
  int nbVertices = chunkRes * ((chunkRes + 1) * 2) + (chunkRes * 2) - 2;
  Vertex *vertices = sceGuGetMemory(sizeof(Vertex) * nbVertices);
  float stepLen = CHUNK_SIZE / chunkRes;

  for (int i = 0; i < chunkRes; i++) {
    float z = i * stepLen;
    for (int j = 0; j <= chunkRes; j++) {
      float x = j * stepLen;
      vertices[index++] = createChunkVertice(pos, x, z);
      vertices[index++] = createChunkVertice(pos, x, z + stepLen);
    }
    if (i < CHUNK_SIZE - 1) {
      vertices[index++] = vertices[index - 1];
      vertices[index++] = createChunkVertice(pos, 0, vertices[index - 1].z);
    }
  }
  sceGumDrawArray(GU_TRIANGLE_STRIP,
                  GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D,
                  nbVertices, 0, vertices);
}