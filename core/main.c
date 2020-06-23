#include "lib.h"

#include "./core.h"
#include "./core_io.h"

// wasm_rt_memory_t *mem;


int main(int argc, char **argv)
{
  init();
  init_core();
  init_core_io();
  // mem = WASM_RT_ADD_PREFIX(Z_memory);

  return Z_mainZ_iii(argc, 1);
}