#include "./lib.h"

wasm_rt_memory_t *mem;
wasm_rt_table_t *table;

void init_mem()
{
  mem = WASM_RT_ADD_PREFIX(Z_memory);
  table = WASM_RT_ADD_PREFIX(Z_table);
}

u32 mem_alloc(u32 size, u32 type)
{
  return WASM_RT_ADD_PREFIX(Z___allocZ_iii)(size, type);
}

u32 mem_retain(u32 ptr)
{
  return WASM_RT_ADD_PREFIX(Z___retainZ_ii)(ptr);
}

void mem_release(u32 ptr)
{
  return WASM_RT_ADD_PREFIX(Z___releaseZ_vi)(ptr);
}
