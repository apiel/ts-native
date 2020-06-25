#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#include "./lib.h"
#include "./mem.h"

#define MAX_TIMER 10

struct timer_thread
{
  pthread_t id;
  bool active;
};

struct timer_thread timer_threads[MAX_TIMER];

struct set_timeout_args
{
  u32 cb;
  u32 ms;
  int8_t id;
};

int8_t get_free_timer_thread_index()
{
  for (uint8_t i = 0; i < MAX_TIMER; i++)
  {
    if (!timer_threads[i].active)
    {
      return i;
    }
  }
  return -1;
}

void join_timers()
{
  for (uint8_t i = 0; i < MAX_TIMER; i++)
  {
    if (timer_threads[i].active)
    {
      pthread_join(timer_threads[i].id, NULL);
    }
  }
}

static void *timeout_timer(void *args_ptr)
{
  struct set_timeout_args *args = args_ptr;

  usleep(args->ms * 1000);
  CALL_INDIRECT(table, void (*)(void), args->cb);

  timer_threads[args->id].active = false;
  pthread_exit(NULL);
}

u32 (*Z_timeZ_coreZ2EsetTimeoutZ_iii)(u32, u32);
u32 core_set_timeout(u32 cb, u32 ms)
{
  int8_t id = get_free_timer_thread_index();

  struct set_timeout_args args;
  args.cb = cb;
  args.ms = ms;
  args.id = id;

  if (id != -1)
  {
    timer_threads[id].active = true;
    int err = pthread_create(&timer_threads[id].id, NULL, timeout_timer, (void *)&args);
    if (!err)
    {
      // pthread_join(timer_threads[id].id, NULL); // if commented then no wait to close
      return id;
    }
    else
    {
      timer_threads[id].active = false;
    }
  }

  return 0;
}

void (*Z_timeZ_coreZ2EclearTimeoutZ_vi)(u32);
void core_clear_timeout(u32 id)
{
  pthread_cancel(timer_threads[id].id);
  timer_threads[id].active = false;
}

void init_core_time()
{
  Z_timeZ_coreZ2EsetTimeoutZ_iii = &core_set_timeout;
  Z_timeZ_coreZ2EclearTimeoutZ_vi = &core_clear_timeout;
}
