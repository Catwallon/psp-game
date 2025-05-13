#include "pggraphics.h"

typedef struct {
  float u, v;
  float nx, ny, nz;
  float x, y, z;
} Vertex;

static fVec3 getNormal(fVec2 pos) {

  fVec3 A = {pos.x, simplex2D((fVec2){pos.x, pos.y + 0.5}), pos.y + 0.5};
  fVec3 B = {pos.x - 1, simplex2D((fVec2){pos.x - 1, pos.y - 0.5}),
             pos.y - 0.5};
  fVec3 C = {pos.x + 1, simplex2D((fVec2){pos.x + 1, pos.y - 0.5}),
             pos.y - 0.5};

  fVec3 vecAB = {B.x - A.x, B.y - A.y, B.z - A.z};
  fVec3 vecAC = {C.x - A.x, C.y - A.y, C.z - A.z};

  return normalizeVec3(crossVec3(vecAC, vecAB));
}

static Vertex createVertex(fVec2 pos) {
  fVec3 normal = getNormal(pos);
  Vertex result = {pos.x,    pos.y, normal.x,       normal.y,
                   normal.z, pos.x, simplex2D(pos), pos.y};
  return result;
}

// TODO: Manage transitions between chunks with different LOD
void generateChunk(GameState *gs) {
  Chunk chunk = gs->terrain.chunkQueue.chunks[gs->terrain.chunkQueue.index];
  if (!chunk.generated) {
    Vertex *buffer = gs->terrain.vBuffer;
    unsigned int index = gs->terrain.chunkQueue.index * NB_VERTICES_CHUNK;
    float stepLen = chunk.size / CHUNK_RESOLUTION;

    buffer[index++] = createVertex((fVec2){chunk.pos.x, chunk.pos.y});
    for (int i = 0; i < CHUNK_RESOLUTION; i++) {
      float z = i * stepLen + chunk.pos.y;
      for (int j = 0; j <= CHUNK_RESOLUTION; j++) {
        float x = j * stepLen + chunk.pos.x;
        buffer[index++] = createVertex((fVec2){x, z});
        buffer[index++] = createVertex((fVec2){x, z + stepLen});
      }
      buffer[index++] =
          createVertex((fVec2){buffer[index - 1].x, buffer[index - 1].z});
      if (i < CHUNK_RESOLUTION - 1) {
        buffer[index++] =
            createVertex((fVec2){chunk.pos.x, buffer[index - 1].z});
      }
    }
    gs->terrain.chunkQueue.chunks[gs->terrain.chunkQueue.index++].generated = 1;
  }
  if (gs->terrain.chunkQueue.index >= NB_CHUNKS)
    gs->terrain.chunkQueue.index = 0;
}

void updateChunkQueue(GameState *gs) {
  int index = 0;
  int chunkDist = 0;
  iVec2 chunkPos = {gs->chunk.x * CHUNK_SIZE, gs->chunk.y * CHUNK_SIZE};

  Chunk chunk = {chunkPos, CHUNK_SIZE, 0};
  gs->terrain.chunkQueue.chunks[index++] = chunk;
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
          Chunk chunk = {(iVec2){posX, posY}, chunkSize, 0};
          gs->terrain.chunkQueue.chunks[index++] = chunk;
        }
      }
    }
    chunkSize *= 3;
  }
}

Terrain initTerrain(GameState *gs) {
  Terrain terrain;

  terrain.vCount = NB_CHUNKS * NB_VERTICES_CHUNK;
  terrain.vBuffer = malloc(terrain.vCount * sizeof(Vertex));
  terrain.vType =
      GU_TEXTURE_32BITF | GU_NORMAL_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D;
  terrain.texture = loadTexture("grass.raw", 128, 128, GU_PSM_8888);

  return terrain;
}