#include "callback.h"
#include "game.h"
#include "gamestate.h"
#include <pspkernel.h>

PSP_MODULE_INFO("PSP Game", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(int argc, char *argv[]) {
  setupCallbacks();
  GameState gs = initGame();
  gameLoop(&gs);
  cleanupGame();

  return 0;
}