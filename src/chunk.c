#include "chunk.h"

float getHeight(float x, float z) { return sinf(x * 0.1f) * cosf(z * 0.1f); }

void drawChunk(GameState *gs, ScePspFVector3 pos) {
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
  int nbVerts = CHUNK_SIZE * (CHUNK_SIZE + 1) * 2 + (CHUNK_SIZE - 1) * 2;
  Vertex *verts = sceGuGetMemory(sizeof(Vertex) * nbVerts);

  for (int i = 0; i < CHUNK_SIZE; i++) {
    for (int j = 0; j < (CHUNK_SIZE + 1) * 2; j++) {
      char odd = j % 2;
      int x = j / 2;
      int z = i + odd;
      verts[index++] =
          createVertex(x, z, x, getHeight(pos.x + x, pos.z + z), z);
    }
    if (i < CHUNK_SIZE - 1) {
      verts[index++] = verts[index - 1];
      int x = 0;
      int z = i + 1;
      verts[index++] =
          createVertex(x, z, x, getHeight(pos.x + x, pos.z + z), z);
    }
  }

  sceGumDrawArray(GU_TRIANGLE_STRIP,
                  GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D,
                  nbVerts, 0, verts);
}