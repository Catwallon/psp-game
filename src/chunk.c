#include "chunk.h"

// TODO: Simplex noise
static float simplex2D(float x, float z) { return sinf(x) * cosf(z); }

static int nbVerticesChunk() {
  return 2 * CHUNK_RESOLUTION * (CHUNK_RESOLUTION + 2);
}

static int nbVerticesMap() {
  return (RENDER_DISTANCE * 8 + 1) * nbVerticesChunk();
}

// TODO: Manage transitions between chunks with different LOD
static void loadChunk(Vector2 chunkPos, int chunkSize, Vertex *guBuffer,
                      int *index) {
  float stepLen = chunkSize / CHUNK_RESOLUTION;
  guBuffer[(*index)++] =
      createVertex(chunkPos.x, chunkPos.y, chunkPos.x,
                   simplex2D(chunkPos.x, chunkPos.y), chunkPos.y);
  for (int i = 0; i < CHUNK_RESOLUTION; i++) {
    float z = i * stepLen + chunkPos.y;
    for (int j = 0; j <= CHUNK_RESOLUTION; j++) {
      float x = j * stepLen + chunkPos.x;
      guBuffer[(*index)++] = createVertex(x, z, x, simplex2D(x, z), z);
      guBuffer[(*index)++] = createVertex(
          x, z + stepLen, x, simplex2D(x, z + stepLen), z + stepLen);
    }
    guBuffer[(*index)++] = createVertex(
        guBuffer[*index - 1].x, guBuffer[*index - 1].z, guBuffer[*index - 1].x,
        simplex2D(guBuffer[*index - 1].x, guBuffer[*index - 1].z),
        guBuffer[*index - 1].z);
    if (i < CHUNK_RESOLUTION - 1) {
      guBuffer[(*index)++] =
          createVertex(chunkPos.x, guBuffer[*index - 1].z, chunkPos.x,
                       simplex2D(chunkPos.x, guBuffer[*index - 1].z),
                       guBuffer[*index - 1].z);
    }
  }
}

void renderMap(GameState *gs) {
  sceGumLoadIdentity();

  sceGuTexMode(GU_PSM_8888, 0, 0, 0);
  sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
  sceGuTexImage(0, gs->textureCache.grass.width, gs->textureCache.grass.height,
                gs->textureCache.grass.width, gs->textureCache.grass.data);
  sceGuTexFilter(GU_LINEAR, GU_LINEAR);
  sceGuTexWrap(GU_REPEAT, GU_REPEAT);

  Vertex *guBuffer = sceGuGetMemory(sizeof(Vertex) * nbVerticesMap());
  Vector2 chunkPos = {gs->chunk.x * CHUNK_SIZE, gs->chunk.y * CHUNK_SIZE};

  int index = 0;
  int chunkDist = 0;
  loadChunk((Vector2){chunkPos.x, chunkPos.y}, CHUNK_SIZE, guBuffer, &index);
  for (int i = 0; i < RENDER_DISTANCE; i++) {
    int chunkSize = CHUNK_SIZE * pow(3, i);
    chunkDist += chunkSize;
    for (char dx = -1; dx <= 1; dx++) {
      for (char dy = -1; dy <= 1; dy++) {
        if (dx || dy) {
          int offsetX = (dx == 1)   ? CHUNK_SIZE + chunkDist - chunkSize
                        : (dx == 0) ? (CHUNK_SIZE - chunkSize) / 2
                                    : -chunkDist;
          int offsetY = (dy == 1)   ? CHUNK_SIZE + chunkDist - chunkSize
                        : (dy == 0) ? (CHUNK_SIZE - chunkSize) / 2
                                    : -chunkDist;
          int posX = chunkPos.x + offsetX;
          int posY = chunkPos.y + offsetY;
          loadChunk((Vector2){posX, posY}, chunkSize, guBuffer, &index);
        }
      }
    }
  }
  sceGumDrawArray(GU_TRIANGLE_STRIP,
                  GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, index,
                  0, guBuffer);
}