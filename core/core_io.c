#include <stdio.h>

#include "./lib.h"
#include "./mem.h"

void (*Z_ioZ_coreZ2EprintZ_vii)(u32, u32);
void core_print(u32 ptr, u32 len)
{
  const uint8_t *buf = (u8 *)mem->data + (u32)(ptr);
  printf("%.*s", len, buf);
  // ToDo: should we release the momory there?
}

void (*Z_ioZ_coreZ2EiprintZ_vi)(u32);
void core_iprint(u32 i)
{
  printf("%u\n", i);
}

void init_core_io()
{
  Z_ioZ_coreZ2EprintZ_vii = &core_print;
  Z_ioZ_coreZ2EiprintZ_vi = &core_iprint;
}
