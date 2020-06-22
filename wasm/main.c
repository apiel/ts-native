#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen
#include <unistd.h> // cwd
#include <linux/limits.h> // cwd

#include "lib.h"

wasm_rt_memory_t *mem;

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
    u32 ptr = WASM_RT_ADD_PREFIX(Z___allocZ_iii)(len << 1, 1);

    uint8_t *buf = (u8 *)mem->data + (u32)(ptr);
    strcpy(buf, cwd);
    // return ptr;

    // seem we need this to ensure it not removed from mem
    u32 ref = WASM_RT_ADD_PREFIX(Z___retainZ_ii)(ptr);
    return ref;
  }
  return 0;
}

// core.print('hello')
void (*Z_ioZ_coreZ2EprintZ_vii)(u32, u32);
void core_print(u32 ptr, u32 len)
{
  const uint8_t *buf = (u8 *)mem->data + (u32)(ptr);
  printf("%.*s", len, buf);
}

int main(int argc, char **argv)
{
  init();
  mem = WASM_RT_ADD_PREFIX(Z_memory);

  Z_envZ_abortZ_viiii = &env_abort;
  Z_coreZ_coreZ2EcwdZ_iv = &core_cwd;
  Z_ioZ_coreZ2EprintZ_vii = &core_print;

  u32 result = Z_mainZ_iii(1, 4);
  printf("res %u\n", result);

  return 0;
}