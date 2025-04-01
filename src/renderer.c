#include "renderer.h"

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
  sceGuFinish();
  sceGuSync(0, 0);

  sceDisplayWaitVblankStart();
  sceGuDisplay(GU_TRUE);
}

void updateCamera(GameState *gs) {
  sceGumMatrixMode(GU_PROJECTION);
  sceGumLoadIdentity();
  sceGumPerspective(75.0f, 16.0f / 9.0f, 0.5f, 1000.0f);

  sceGumMatrixMode(GU_VIEW);
  sceGumLoadIdentity();
  {

    ScePspFVector3 invRot = {-gs->playerRot.x, -gs->playerRot.y,
                             -gs->playerRot.z};
    sceGumRotateXYZ(&invRot);
    ScePspFVector3 invPos = {-gs->playerPos.x, -gs->playerPos.y,
                             -gs->playerPos.z};
    sceGumTranslate(&invPos);
    sceGumUpdateMatrix();
  }
}

void renderGame(GameState *gs) {
  sceGuStart(GU_DIRECT, list);

  sceGuClearColor(0xffffffff);
  sceGuClearDepth(0);
  sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

  updateCamera(gs);

  sceGumMatrixMode(GU_MODEL);
  drawChunk(gs, (ScePspFVector3){0.0f, 0.0f, 0.0f}, 16);
  drawChunk(gs, (ScePspFVector3){0.0f, 0.0f, -CHUNK_SIZE}, 8);
  drawChunk(gs, (ScePspFVector3){CHUNK_SIZE, 0.0f, 0.0f}, 8);
  drawChunk(gs, (ScePspFVector3){0.0f, 0.0f, CHUNK_SIZE}, 8);
  drawChunk(gs, (ScePspFVector3){-CHUNK_SIZE, 0.0f, 0.0f}, 8);

  sceGuFinish();
  sceGuSync(0, 0);
  sceDisplayWaitVblankStart();
  sceGuSwapBuffers();
}

void cleanupGu() { sceGuTerm(); }