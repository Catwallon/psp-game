#pragma once

#include "pgmath.h"
#include "pgtypes.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspkernel.h>
#include <psprtc.h>
#include <stdio.h>

// callback.c
int setupCallbacks(void);

// input.c
void initInput();
void handleInput(GameState *gs);
char isPressed(GameState *gs, enum PspCtrlButtons button);
char isJustPressed(GameState *gs, enum PspCtrlButtons button);
unsigned char getAnalogX(GameState *gs);
unsigned char getAnalogY(GameState *gs);

// tools.c
float getDeltaTime(GameState *gs);
unsigned int getFPS(GameState *gs);

// debug.c
void initDebug();
void displayDebug(GameState *gs);
void printDebug(GameState *gs);

// error.c
void exitError(char *msg);