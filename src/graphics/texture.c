#include "pggraphics.h"

Texture loadTexture(char *path, unsigned int width, unsigned int height,
                    int type) {
  Texture texture;
  FILE *file = fopen(path, "rb");
  fseek(file, 0, SEEK_END);
  unsigned int size = ftell(file);
  fseek(file, 0, SEEK_SET);
  texture.buffer = malloc(size);
  fread(texture.buffer, 1, size, file);
  fclose(file);

  texture.width = width;
  texture.height = height;
  texture.type = type;

  return texture;
}