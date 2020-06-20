#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

void (*Z_envZ_abortZ_viiii)(u32, u32, u32, u32);

void env_abort(u32 a, u32 b, u32 c, u32 d)
{
  abort();
}

int main(int argc, char **argv)
{
  init();
  Z_envZ_abortZ_viiii = &env_abort;
  u32 result = Z_mainZ_iii(1, 4);
  printf("res %u\n", result);

  return 0;
}