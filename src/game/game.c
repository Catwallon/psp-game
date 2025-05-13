#include "pggame.h"
#include <stdio.h>

GameState initGame() {
  GameState gs;
  fVec3 playerPos = {0.0f, 1.8f, 0.0f};
  fVec3 playerRot = {0.0f, degToRad(180.0f), 0.0f};

  initGu(&gs);
  initInput();
  initDebug();
  gs.playerPos = playerPos;
  gs.playerRot = playerRot;
  iVec2 chunk = {gs.playerPos.x / CHUNK_SIZE, gs.playerPos.z / CHUNK_SIZE};
  gs.chunk = chunk;
  gs.debug = 1;
  gs.tick = 0;
  gs.previousTick = 0;
  gs.modelCache = initModelCache();
  gs.terrain = initTerrain(&gs);
  updateChunkQueue(&gs);

  return gs;
}

void updateGame(GameState *gs) {
  gs->previousTick = gs->tick;
  sceRtcGetCurrentTick(&gs->tick);
  float deltaTime = getDeltaTime(gs);

  float forwardX = sinf(gs->playerRot.y);
  float forwardZ = cosf(gs->playerRot.y);
  float rightX = cosf(gs->playerRot.y);
  float rightZ = -sinf(gs->playerRot.y);

  // Move forward / backward
  gs->playerPos.x +=
      (getAnalogY(gs) / 128.0f - 1.0f) * forwardX * PLAYER_SPEED * deltaTime;
  gs->playerPos.z +=
      (getAnalogY(gs) / 128.0f - 1.0f) * forwardZ * PLAYER_SPEED * deltaTime;

  // Move left / right
  gs->playerPos.x +=
      (getAnalogX(gs) / 128.0f - 1.0f) * rightX * PLAYER_SPEED * deltaTime;
  gs->playerPos.z +=
      (getAnalogX(gs) / 128.0f - 1.0f) * rightZ * PLAYER_SPEED * deltaTime;

  // Move up
  if (isPressed(gs, PSP_CTRL_UP))
    gs->playerPos.y += PLAYER_SPEED * deltaTime;

  // Move down
  if (isPressed(gs, PSP_CTRL_DOWN))
    gs->playerPos.y -= PLAYER_SPEED * deltaTime;

  // Rotate left
  if (isPressed(gs, PSP_CTRL_SQUARE))
    gs->playerRot.y += SENSIVITY * deltaTime;

  // Rotate right
  if (isPressed(gs, PSP_CTRL_CIRCLE))
    gs->playerRot.y -= SENSIVITY * deltaTime;

  // Rotate up
  if (isPressed(gs, PSP_CTRL_TRIANGLE)) {
    float newPlayerRotX = gs->playerRot.x + SENSIVITY * deltaTime;
    if (radToDeg(newPlayerRotX) <= MAX_X_ANGLE)
      gs->playerRot.x = newPlayerRotX;
    else
      gs->playerRot.x = degToRad(MAX_X_ANGLE);
  }

  // Rotate down
  if (isPressed(gs, PSP_CTRL_CROSS)) {
    float newPlayerRotX = gs->playerRot.x - SENSIVITY * deltaTime;
    if (radToDeg(newPlayerRotX) >= -MAX_X_ANGLE)
      gs->playerRot.x = newPlayerRotX;
    else
      gs->playerRot.x = -degToRad(MAX_X_ANGLE);
  }

  // Enable / Disable debug
  if (isJustPressed(gs, PSP_CTRL_SELECT))
    gs->debug = !gs->debug;

  // Update current chunk
  iVec2 chunk = {gs->playerPos.x / CHUNK_SIZE - (gs->playerPos.x < 0),
                 gs->playerPos.z / CHUNK_SIZE - (gs->playerPos.z < 0)};
  if (chunk.x != gs->chunk.x || chunk.y != gs->chunk.y) {
    gs->chunk = chunk;
    updateChunkQueue(gs);
  }
  generateChunk(gs);
}

void gameLoop(GameState *gs) {
  while (1) {
    handleInput(gs);
    updateGame(gs);
    renderGame(gs);
    if (gs->debug)
      displayDebug(gs);
    printDebug(gs);
  }
}

void cleanupGame() {
  cleanupGu();
  sceKernelExitGame();
}