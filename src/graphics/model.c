#include "pggraphics.h"

ModelCache initModelCache(GameState *gs) {
  ModelCache modelCache;

  modelCache.terrain = initTerrainModel(gs);

  return modelCache;
}