#include "game.h"

void initGame() { initGu(); }

void gameLoop() {
  while (1) {
    renderGame();
  }
}

void cleanupGame() {
  cleanupGu();
  sceKernelExitGame();
}