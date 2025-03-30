#include "game.h"

GameState initGame() {
  GameState gs;
  ScePspFVector3 playerPos = {0.0f, 0.0f, 0.0f};
  ScePspFVector3 playerRot = {0.0f, 0.0f, 0.0f};

  gs.playerPos = playerPos;
  gs.playerRot = playerRot;
  initGu();
  initInput();
  return gs;
}

void updateGame(GameState *gs) {
  float forwardX = sinf(gs->playerRot.y);
  float forwardZ = cosf(gs->playerRot.y);
  float rightX = cosf(gs->playerRot.y);
  float rightZ = -sinf(gs->playerRot.y);

  // Move forward / backward
  gs->playerPos.x += (getAnalogY(gs) - 128) * forwardX * PLAYER_SPEED;
  gs->playerPos.z += (getAnalogY(gs) - 128) * forwardZ * PLAYER_SPEED;

  // Move left / right
  gs->playerPos.x += (getAnalogX(gs) - 128) * rightX * PLAYER_SPEED;
  gs->playerPos.z += (getAnalogX(gs) - 128) * rightZ * PLAYER_SPEED;

  if (isPressed(gs, PSP_CTRL_SQUARE)) {
    gs->playerRot.y += SENSIVITY;
  }
  if (isPressed(gs, PSP_CTRL_CIRCLE)) {
    gs->playerRot.y -= SENSIVITY;
  }
  if (isPressed(gs, PSP_CTRL_TRIANGLE)) {
    float newPlayerRotX = gs->playerRot.x + SENSIVITY;
    if (radToDeg(newPlayerRotX) <= MAX_X_ANGLE)
      gs->playerRot.x = newPlayerRotX;
    else
      gs->playerRot.x = degToRad(MAX_X_ANGLE);
  }
  if (isPressed(gs, PSP_CTRL_CROSS)) {
    float newPlayerRotX = gs->playerRot.x - SENSIVITY;
    if (radToDeg(newPlayerRotX) >= -MAX_X_ANGLE)
      gs->playerRot.x = newPlayerRotX;
    else
      gs->playerRot.x = -degToRad(MAX_X_ANGLE);
  }
}

void gameLoop(GameState *gs) {
  while (1) {
    handleInput(gs);
    updateGame(gs);
    renderGame(gs);
  }
}

void cleanupGame() {
  cleanupGu();
  sceKernelExitGame();
}