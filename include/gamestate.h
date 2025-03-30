#pragma once

#include <pspctrl.h>
#include <pspkernel.h>

typedef struct {
  ScePspFVector3 playerPos;
  ScePspFVector3 playerRot;
  SceCtrlData pad;
  SceCtrlData previousPad;
  unsigned long long tick;
  unsigned long long previousTick;
  char debug;
} GameState;