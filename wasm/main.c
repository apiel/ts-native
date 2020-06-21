#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

wasm_rt_memory_t *mem;

void (*Z_envZ_abortZ_viiii)(u32, u32, u32, u32);

void env_abort(u32 a, u32 b, u32 c, u32 d)
{
  abort();
}

// core.test(4)
void (*Z_indexZ_coreZ2EabcZ_vi)(u32);
void core_abc(u32 a)
{
  printf("abc %u\n", a);
}

// core.print('hello')
void (*Z_indexZ_coreZ2EprintZ_vii)(u32, u32);
void core_print(u32 ptr, u32 len)
{
  const uint8_t *buf = (u8 *)mem->data + (u32)(ptr);
  printf("%s", buf);
}

int main(int argc, char **argv)
{
  init();
  mem = WASM_RT_ADD_PREFIX(Z_memory);

  Z_envZ_abortZ_viiii = &env_abort;
  Z_indexZ_coreZ2EabcZ_vi = &core_abc;
  Z_indexZ_coreZ2EprintZ_vii = &core_print;

  u32 result = Z_mainZ_iii(1, 4);
  printf("res %u\n", result);

  return 0;
}