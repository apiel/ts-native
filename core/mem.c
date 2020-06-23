#include "./lib.h"

wasm_rt_memory_t *mem;

void init_mem() {
  mem = WASM_RT_ADD_PREFIX(Z_memory);
}
