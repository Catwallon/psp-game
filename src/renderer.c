#include "renderer.h"

static unsigned int __attribute__((aligned(16))) list[262144];

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

void renderGame() {
  sceGuStart(GU_DIRECT, list);

  sceGuClearColor(0xffffffff);
  sceGuClearDepth(0);
  sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

  sceGumMatrixMode(GU_PROJECTION);
  sceGumLoadIdentity();
  sceGumPerspective(75.0f, 16.0f / 9.0f, 0.5f, 1000.0f);

  sceGumMatrixMode(GU_VIEW);
  sceGumLoadIdentity();

  sceGumMatrixMode(GU_MODEL);
  sceGumLoadIdentity();
  {
    ScePspFVector3 pos = {0, 0, -2.5f};
    sceGumTranslate(&pos);
  }

  Vertex *vertices = (Vertex *)sceGuGetMemory(3 * sizeof(Vertex));

  vertices[0].x = -1;
  vertices[0].y = -1;
  vertices[0].z = 0;

  vertices[1].x = 0;
  vertices[1].y = 1;
  vertices[1].z = 0;

  vertices[2].x = 1;
  vertices[2].y = -1;
  vertices[2].z = 0;

  sceGumDrawArray(GU_TRIANGLES, GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, 0,
                  vertices);

  sceGuFinish();
  sceGuSync(0, 0);

  sceDisplayWaitVblankStart();
  sceGuSwapBuffers();
}

void cleanupGu() { sceGuTerm(); }