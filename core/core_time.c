#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "./lib.h"
#include "./mem.h"

struct set_timeout_args
{
  u32 cb;
  u32 ms;
};

static void *timeout_timer(void *args_ptr)
{
  struct set_timeout_args * args = args_ptr;

  usleep(args->ms * 1000);
  CALL_INDIRECT(table, void (*)(void), args->cb);

  pthread_exit(NULL);
}

u32 (*Z_timeZ_coreZ2EsetTimeoutZ_iii)(u32, u32);
u32 core_set_timeout(u32 cb, u32 ms)
{
  struct set_timeout_args args;
  args.cb = cb;
  args.ms = ms;

  pthread_t thread_id;
  int rc = pthread_create(&thread_id, NULL, timeout_timer, (void *)&args);
  if (rc)
    printf("=== Failed to create thread\n");

  pthread_join(thread_id, NULL);
  return 123;
}

void init_core_time()
{
  Z_timeZ_coreZ2EsetTimeoutZ_iii = &core_set_timeout;
}
