#include "pggraphics.h"
#include <stdio.h>

typedef struct {
  float u, v;
  float nx, ny, nz;
  float x, y, z;
} Vertex;

fVec3 calculateNormal(fVec2 pos) {

  fVec3 A = {pos.x, simplex2D((fVec2){pos.x, pos.y + 0.5}), pos.y + 0.5};
  fVec3 B = {pos.x - 1, simplex2D((fVec2){pos.x - 1, pos.y - 0.5}),
             pos.y - 0.5};
  fVec3 C = {pos.x + 1, simplex2D((fVec2){pos.x + 1, pos.y - 0.5}),
             pos.y - 0.5};

  fVec3 vecAB = {B.x - A.x, B.y - A.y, B.z - A.z};
  fVec3 vecAC = {C.x - A.x, C.y - A.y, C.z - A.z};

  return normalizeVec3(crossVec3(vecAC, vecAB));
}

Vertex createVertex(fVec2 pos) {
  fVec3 normal = calculateNormal(pos);
  Vertex result = {pos.x,    pos.y, normal.x,       normal.y,
                   normal.z, pos.x, simplex2D(pos), pos.y};
  return result;
}

static unsigned int nbVerticesChunk() {
  return 2 * CHUNK_RESOLUTION * (CHUNK_RESOLUTION + 2);
}

static unsigned int nbVerticesTerrain() {
  return (RENDER_DISTANCE * 8 + 1) * nbVerticesChunk();
}

// TODO: Manage transitions between chunks with different LOD
static void generateChunk(iVec2 chunkPos, int chunkSize, Vertex *buffer,
                          unsigned int *index) {
  float stepLen = chunkSize / CHUNK_RESOLUTION;
  buffer[(*index)++] = createVertex((fVec2){chunkPos.x, chunkPos.y});
  for (int i = 0; i < CHUNK_RESOLUTION; i++) {
    float z = i * stepLen + chunkPos.y;
    for (int j = 0; j <= CHUNK_RESOLUTION; j++) {
      float x = j * stepLen + chunkPos.x;
      buffer[(*index)++] = createVertex((fVec2){x, z});
      buffer[(*index)++] = createVertex((fVec2){x, z + stepLen});
    }
    buffer[(*index)++] =
        createVertex((fVec2){buffer[*index - 1].x, buffer[*index - 1].z});
    if (i < CHUNK_RESOLUTION - 1) {
      buffer[(*index)++] =
          createVertex((fVec2){chunkPos.x, buffer[*index - 1].z});
    }
  }
}

void updateTerrainBuffer(GameState *gs) {
  Vertex *buffer = gs->modelCache.terrain.buffer;
  int index = 0;
  int chunkDist = 0;
  iVec2 chunkPos = {gs->chunk.x * CHUNK_SIZE, gs->chunk.y * CHUNK_SIZE};
  generateChunk(chunkPos, CHUNK_SIZE, buffer, &index);
  int chunkSize = CHUNK_SIZE;
  for (int i = 0; i < RENDER_DISTANCE; i++) {
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
          generateChunk((iVec2){posX, posY}, chunkSize, buffer, &index);
        }
      }
    }
    chunkSize *= 3;
  }
}

Model initTerrainModel(GameState *gs) {
  Model terrain;

  terrain.size = nbVerticesTerrain();
  terrain.buffer = sceGuGetMemory(terrain.size * sizeof(Vertex));
  terrain.type =
      GU_TEXTURE_32BITF | GU_NORMAL_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D;
  terrain.texture = gs->textureCache.grass;

  return terrain;
}