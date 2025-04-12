
#include "pgutils.h"

static int exitCallback(int arg1, int arg2, void *common) {
  sceKernelExitGame();

  return 0;
}

static int callbackThread(SceSize args, void *argp) {
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();

  return 0;
}

int setupCallbacks(void) {
  int thid = 0;
  thid = sceKernelCreateThread("Callback Thread", callbackThread, 0x11, 0xFA0,
                               THREAD_ATTR_USER, 0);
  if (thid >= 0)
    sceKernelStartThread(thid, 0, 0);
  return thid;
}
