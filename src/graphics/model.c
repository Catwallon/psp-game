#include "pggraphics.h"
#include "pgtypes.h"

typedef struct {
  float x, y, z;
} V;

typedef struct {
  float x, y, z;
} Vn;

typedef struct {
  float u, v;
} Vt;

// Only support OBJ files stricly using triangle faces, textures coordinates and
// normales
static Model loadModel(char *path, Texture texture) {
  Model model;
  char line[100];

  FILE *file = fopen(path, "r");
  if (file == NULL) {
    exitError("Can't opening file");
  }

  model.vCount = 0;
  model.vType =
      GU_TEXTURE_32BITF | GU_NORMAL_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D;
  model.prim = GU_TRIANGLES;
  unsigned int vCount = 0;
  unsigned int vnCount = 0;
  unsigned int vtCount = 0;
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v' && line[1] == 'n')
      vnCount++;
    else if (line[0] == 'v' && line[1] == 't')
      vtCount++;
    else if (line[0] == 'v')
      vCount++;
    else if (line[0] == 'f')
      model.vCount += 3;
  }

  model.texture = texture;
  model.vBuffer = malloc(model.vCount * sizeof(float) * 8);
  V *vBuffer = malloc(vCount * sizeof(V));
  Vn *vnBuffer = malloc(vnCount * sizeof(Vn));
  Vt *vtBuffer = malloc(vtCount * sizeof(Vt));
  if (!model.vBuffer || !vBuffer || !vnBuffer || !vBuffer) {
    exitError("Malloc failed");
  }

  rewind(file);

  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  while (fgets(line, sizeof(line), file)) {
    // fprintf(stdout, "%s\n", line);
    if (line[0] == 'v' && line[1] == 'n') {
      if (sscanf(line, "vn %f %f %f", &vnBuffer[i].x, &vnBuffer[i].y,
                 &vnBuffer[i].z) != 3) {
        exitError("Invalid .obj file");
      }
      i++;
    } else if (line[0] == 'v' && line[1] == 't') {
      if (sscanf(line, "vt %f %f", &vtBuffer[k].u, &vtBuffer[k].v) != 2) {
        exitError("Invalid .obj file");
      }
      k++;
    } else if (line[0] == 'v') {
      if (sscanf(line, "v %f %f %f", &vBuffer[j].x, &vBuffer[j].y,
                 &vBuffer[j].z) != 3) {
        exitError("Invalid .obj file");
      }
      j++;
    } else if (line[0] == 'f') {
      unsigned int indexes[9];
      if (sscanf(line, "f %u/%u/%u  %u/%u/%u  %u/%u/%u", &indexes[0],
                 &indexes[1], &indexes[2], &indexes[3], &indexes[4],
                 &indexes[5], &indexes[6], &indexes[7], &indexes[8]) != 9) {
        exitError("Invalid .obj file");
      }
      for (int m = 0; m < 3; m++) {
        model.vBuffer[l++] = vtBuffer[indexes[(m * 3) + 1] - 1].u;
        model.vBuffer[l++] = vtBuffer[indexes[(m * 3) + 1] - 1].v;

        model.vBuffer[l++] = vnBuffer[indexes[(m * 3) + 2] - 1].x;
        model.vBuffer[l++] = vnBuffer[indexes[(m * 3) + 2] - 1].y;
        model.vBuffer[l++] = vnBuffer[indexes[(m * 3) + 2] - 1].z;

        model.vBuffer[l++] = vBuffer[indexes[m * 3] - 1].x;
        model.vBuffer[l++] = vBuffer[indexes[m * 3] - 1].y;
        model.vBuffer[l++] = vBuffer[indexes[m * 3] - 1].z;
      }
    }
  }
  free(vBuffer);
  free(vnBuffer);
  free(vtBuffer);
  fclose(file);
  return model;
}

ModelCache initModelCache() {
  ModelCache modelCache;
  modelCache.knight = loadModel(
      "./knight.obj", loadTexture("./knight.raw", 256, 256, GU_PSM_8888));
  return modelCache;
}