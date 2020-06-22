#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen

#include "lib.h"

wasm_rt_memory_t *mem;

void (*Z_envZ_abortZ_viiii)(u32, u32, u32, u32);

void env_abort(u32 a, u32 b, u32 c, u32 d)
{
  abort();
}

// core.test(4)
u32 (*Z_indexZ_coreZ2EabcZ_ii)(u32);
u32 core_abc(u32 a)
{
  printf("abc %u\n", a);

  char * ret = "RET core_abc";
  // &(WASM_RT_ADD_PREFIX(Z___allocZ_iii)
  // __retain(__allocString(aStr))
  int len = strlen(ret);
  u32 ptr = WASM_RT_ADD_PREFIX(Z___allocZ_iii)(len << 1, 1);

  uint8_t *buf = (u8 *)mem->data + (u32)(ptr);
  // buf[0] = 'R';
  // buf[1] = 'E';
  // buf[2] = 'T';
  // buf[3] = '\0';
  strcpy(buf, ret);
  // return ptr;

  // seem we need this to ensure it not removed from mem
  u32 ref = WASM_RT_ADD_PREFIX(Z___retainZ_ii)(ptr);
  return ref;
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
  Z_indexZ_coreZ2EabcZ_ii = &core_abc;
  Z_indexZ_coreZ2EprintZ_vii = &core_print;

  u32 result = Z_mainZ_iii(1, 4);
  printf("res %u\n", result);

  return 0;
}