#include <stdlib.h> // abort
#include <string.h> // strlen
#include <unistd.h> // cwd
#include <linux/limits.h> // cwd

#include "lib.h"

void (*Z_envZ_abortZ_viiii)(u32, u32, u32, u32);
void env_abort(u32 a, u32 b, u32 c, u32 d)
{
  abort();
}

u32 (*Z_coreZ_coreZ2EcwdZ_iv)();
u32 core_cwd()
{
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    // printf("Current working dir: %s\n", cwd);
    // char *ret = "RET core_abc";
    int len = strlen(cwd);
    u32 ptr = WASM_RT_ADD_PREFIX(Z___allocZ_iii)((len + 1) << 1, 1);

    uint8_t *buf = (u8 *)(WASM_RT_ADD_PREFIX(Z_memory))->data + (u32)(ptr);
    buf[0] = len;
    buf++;
    strcpy(buf, cwd);
    // return ptr;

    // seem we need this to ensure it not removed from mem
    u32 ref = WASM_RT_ADD_PREFIX(Z___retainZ_ii)(ptr);
    return ref;
  }
  return 0;
}

void init_core() {
  Z_envZ_abortZ_viiii = &env_abort;
  Z_coreZ_coreZ2EcwdZ_iv = &core_cwd;
}
