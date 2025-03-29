#pragma once

#include <pspctrl.h>

typedef struct {
  float playerX;
  float playerZ;
  SceCtrlData pad;
} GameState;