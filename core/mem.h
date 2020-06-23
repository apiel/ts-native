#ifndef MEM_H_
#define MEM_H_

#include "./lib.h"

wasm_rt_memory_t *mem;

void init_mem();
u32 mem_alloc(u32 size, u32 type);
u32 mem_retain(u32 ptr);
void mem_release(u32 ptr);

#endif