#include <stdlib.h> // abort

#include "./lib.h"

#include "./mem.h"
#ifdef INC_Z_COREZ_COREZ
#include "./core.h"
#endif
#ifdef INC_Z_IOZ_COREZ
#include "./core_io.h"
#endif

void (*Z_envZ_abortZ_viiii)(u32, u32, u32, u32);
void env_abort(u32 a, u32 b, u32 c, u32 d)
{
  abort();
}

int main(int argc, char **argv)
{
  init();
  init_mem();
  Z_envZ_abortZ_viiii = &env_abort;

  #ifdef INC_Z_COREZ_COREZ
  init_core();
  #endif
  #ifdef INC_Z_IOZ_COREZ
  init_core_io();
  #endif

  return Z_mainZ_iii(argc, 1);
}