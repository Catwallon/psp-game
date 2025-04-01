#pragma once

#include <pspkernel.h>

typedef struct {
  int width;
  int height;
  unsigned char *data;
} Texture;

typedef struct {
  Texture grass;
} TextureCache;

extern unsigned char grass_start[];

TextureCache initTextureCache();
