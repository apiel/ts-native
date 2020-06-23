#include <string.h> // strlen
#include <unistd.h> // cwd
#include <linux/limits.h> // cwd

#include "./lib.h"
#include "./mem.h"

u32 (*Z_coreZ_coreZ2EcwdZ_iv)();
u32 core_cwd()
{
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    // printf("Current working dir: %s\n", cwd);
    // char *ret = "RET core_abc";
    int len = strlen(cwd);
    u32 ptr = mem_alloc((len + 1) << 1, 1);

    uint8_t *buf = (u8 *)mem->data + (u32)(ptr);
    buf[0] = len;
    buf++;
    strcpy(buf, cwd);
    // return ptr;

    // seem we need this to ensure it not removed from mem
    u32 ref = mem_retain(ptr);
    return ref;
  }
  return 0;
}

void init_core() {
  Z_coreZ_coreZ2EcwdZ_iv = &core_cwd;
}
