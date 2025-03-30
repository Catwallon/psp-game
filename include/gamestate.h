#pragma once

#include <pspctrl.h>
#include <pspkernel.h>

typedef struct {
  ScePspFVector3 playerPos;
  ScePspFVector3 playerRot;
  SceCtrlData pad;
} GameState;