#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "./lib.h"
#include "./mem.h"

/* call back function - inform the user the time has expired */
void timeout_cb()
{
  printf("=== your time is up ===\n");
}

/* Go to sleep for a period of seconds */
static void *g_start_timer(void *args)
{
  /* function pointer */
  void (*function_pointer)();

  /* cast the seconds passed in to int and
     * set this for the period to wait */
  int seconds = *((int *)args);
  printf("go to sleep for %d\n", seconds);

  /* assign the address of the cb to the function pointer */
  function_pointer = timeout_cb;

  sleep(seconds);
  /* call the cb to inform the user time is out */
  (*function_pointer)();

  pthread_exit(NULL);
}

u32 (*Z_timeZ_coreZ2EsetTimeoutZ_iii)(u32, u32);
u32 core_set_timeout(u32 cb, u32 ms)
{
  printf("call setTimeout %u\n", cb);

  // void (*buf)();
  // buf = (void (*)(void *))table->data + cb;
  // (*buf)();

  CALL_INDIRECT(table, void (*)(void), cb);
  // ((void (*)(void))table->data[cb].func)();

  // pthread_t thread_id;
  // int seconds = 3;
  // int rc;

  // rc = pthread_create(&thread_id, NULL, g_start_timer, (void *)&seconds);
  // if (rc)
  //   printf("=== Failed to create thread\n");

  // pthread_join(thread_id, NULL);

  // printf("=== End of Program - all threads in ===\n");
  return 123;
}

void init_core_time()
{
  Z_timeZ_coreZ2EsetTimeoutZ_iii = &core_set_timeout;
}
