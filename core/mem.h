#ifndef MEM_H_
#define MEM_H_

#include "./lib.h"

wasm_rt_memory_t *mem;
wasm_rt_table_t *table;

#define TRAP(x) (wasm_rt_trap(WASM_RT_TRAP_##x), 0)

#define CALL_INDIRECT(table, t, x, ...)          \
    (x < table->size && table->data[x].func      \
         ? ((t)table->data[x].func)(__VA_ARGS__) \
         : TRAP(CALL_INDIRECT))

void init_mem();
u32 mem_alloc(u32 size, u32 type);
u32 mem_retain(u32 ptr);
void mem_release(u32 ptr);

#endif