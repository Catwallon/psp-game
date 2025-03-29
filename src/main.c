#include "game.h"
#include <pspkernel.h>

PSP_MODULE_INFO("PSP Game", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(int argc, char *argv[]) {
  initGame();
  gameLoop();
  cleanupGame();

  return 0;
}