#include "game.h"

GameState initGame() {
  GameState gs;
  gs.playerX = 0;
  gs.playerZ = 0;

  initGu();

  return gs;
}

void update_game(GameState *gs) {
  if (isPressed(gs, PSP_CTRL_RIGHT)) {
    gs->playerX += PLAYER_SPEED;
  }
  if (isPressed(gs, PSP_CTRL_LEFT)) {
    gs->playerX -= PLAYER_SPEED;
  }
  if (isPressed(gs, PSP_CTRL_UP)) {
    gs->playerZ -= PLAYER_SPEED;
  }
  if (isPressed(gs, PSP_CTRL_DOWN)) {
    gs->playerZ += PLAYER_SPEED;
  }
}

void gameLoop(GameState *gs) {
  while (1) {
    handleInput(gs);
    update_game(gs);
    renderGame(gs);
  }
}

void cleanupGame() {
  cleanupGu();
  sceKernelExitGame();
}