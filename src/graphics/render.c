#include "pggraphics.h"
#include <stdio.h>

static int __attribute__((aligned(16))) list[262144];

void initGu() {

  void *fbp0 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
  void *fbp1 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
  void *zbp = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_4444);

  sceGuInit();
  sceGuStart(GU_DIRECT, list);
  sceGuDrawBuffer(GU_PSM_8888, fbp0, BUF_WIDTH);
  sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
  sceGuDepthBuffer(zbp, BUF_WIDTH);
  sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
  sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
  sceGuDepthRange(65535, 0);
  sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
  sceGuEnable(GU_SCISSOR_TEST);
  sceGuDepthFunc(GU_GEQUAL);
  sceGuEnable(GU_DEPTH_TEST);
  sceGuFrontFace(GU_CW);
  sceGuShadeModel(GU_SMOOTH);
  sceGuEnable(GU_CULL_FACE);
  sceGuEnable(GU_TEXTURE_2D);
  sceGuEnable(GU_CLIP_PLANES);
  sceGuEnable(GU_LIGHTING);
  sceGuEnable(GU_LIGHT0);
  sceDisplayWaitVblankStart();
  sceGuDisplay(GU_TRUE);
  sceGuFinish();
  sceGuSync(0, 0);
}

static void updateCamera(GameState *gs) {
  sceGumMatrixMode(GU_PROJECTION);
  sceGumLoadIdentity();
  sceGumPerspective(FOV, 16.0f / 9.0f, 1.0f, 1000.0f);

  sceGumMatrixMode(GU_VIEW);
  sceGumLoadIdentity();
  {
    fVec3 invRot = {-gs->playerRot.x, -gs->playerRot.y, -gs->playerRot.z};
    sceGumRotateXYZ(&invRot);
    fVec3 invPos = {-gs->playerPos.x, -gs->playerPos.y, -gs->playerPos.z};
    sceGumTranslate(&invPos);
    sceGumUpdateMatrix();
  }
}

static void drawTerrain(Terrain terrain) {
  sceGumMatrixMode(GU_MODEL);

  sceGumLoadIdentity();

  Texture texture = terrain.texture;
  sceGuTexMode(GU_PSM_8888, 0, 0, 0);
  sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGB);
  sceGuTexImage(0, texture.width, texture.height, texture.width, texture.data);
  sceGuTexFilter(GU_LINEAR, GU_LINEAR);
  sceGuTexWrap(GU_REPEAT, GU_REPEAT);

  sceGumDrawArray(GU_TRIANGLE_STRIP, terrain.vType, terrain.vCount, 0,
                  terrain.vBuffer);
}

void renderGame(GameState *gs) {
  sceGuStart(GU_DIRECT, list);

  sceGuClearColor(0xfffce3a7);
  sceGuClearDepth(0);
  sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

  sceGuLight(0, GU_DIRECTIONAL, GU_DIFFUSE_AND_SPECULAR,
             &(fVec3){1.0f, 1.0f, 1.0f});
  sceGuLightColor(0, GU_DIFFUSE_AND_SPECULAR, 0xffffffff);
  sceGuSpecular(12.0f);
  sceGuAmbientColor(0xffffffff);
  sceGuColor(0xffffffff);

  updateCamera(gs);

  drawTerrain(gs->terrain);

  sceGuFinish();
  sceGuSync(0, 0);
  sceDisplayWaitVblankStart();
  sceGuSwapBuffers();
}

void cleanupGu() { sceGuTerm(); }