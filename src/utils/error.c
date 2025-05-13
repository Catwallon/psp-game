#include "pgutils.h"

void exitError(char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  sceKernelExitGame();
}