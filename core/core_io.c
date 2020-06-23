#include <stdio.h>

#include "lib.h"

// core.print('hello')
void (*Z_ioZ_coreZ2EprintZ_vii)(u32, u32);
void core_print(u32 ptr, u32 len)
{
  const uint8_t *buf = (u8 *)(WASM_RT_ADD_PREFIX(Z_memory))->data + (u32)(ptr);
  printf("%.*s", len, buf);
}

void init_core_io() {
  Z_ioZ_coreZ2EprintZ_vii = &core_print;
}
