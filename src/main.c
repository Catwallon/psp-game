#include "pggame.h"
#include "pgtypes.h"
#include "pgutils.h"
#include <pspkernel.h>

PSP_MODULE_INFO("PSP Game", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main() {
  setupCallbacks();
  GameState gs = initGame();
  gameLoop(&gs);
  cleanupGame();

  return 0;
}