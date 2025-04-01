#include "texture.h"

extern unsigned char grass_start[];

TextureCache initTextureCache() {
  TextureCache textureCache;
  textureCache.grass.width = 128;
  textureCache.grass.height = 128;
  textureCache.grass.data = grass_start;

  return textureCache;
}