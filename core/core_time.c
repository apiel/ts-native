#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./lib.h"
#include "./mem.h"

#define MAX_TIMER 10

struct timer_thread {
    pthread_t thread;
    bool active;
    u32 cb;
    u32 ms;
};

struct timer_thread timer_threads[MAX_TIMER];

int8_t get_free_timer_thread_index() {
    for (uint8_t i = 0; i < MAX_TIMER; i++) {
        if (!timer_threads[i].active) {
            return i;
        }
    }
    return -1;
}

void join_timers() {
    for (uint8_t i = 0; i < MAX_TIMER; i++) {
        if (timer_threads[i].active) {
            pthread_join(timer_threads[i].thread, NULL);
        }
    }
}

static void *timeout_timer(void *id_ptr) {
    int8_t id = *((int *)id_ptr);

    usleep(timer_threads[id].ms * 1000);
    CALL_INDIRECT(table, void (*)(void), timer_threads[id].cb);

    timer_threads[id].active = false;
    free(id_ptr);
    pthread_exit(NULL);
}

u32 (*Z_timeZ_coreZ2EsetTimeoutZ_iii)(u32, u32);
u32 core_set_timeout(u32 cb, u32 ms) {
    int8_t id = get_free_timer_thread_index();
    if (id != -1) {
        timer_threads[id].active = true;
        timer_threads[id].ms = ms;
        timer_threads[id].cb = cb;
        int8_t *id_ptr = malloc(sizeof(int8_t));
        *id_ptr = id;
        int err = pthread_create(&timer_threads[id].thread, NULL, timeout_timer,
                                 (void *)id_ptr);
        if (!err) {
            return id;
        } else {
            timer_threads[id].active = false;
        }
    }

    return 0;
}

void (*Z_timeZ_coreZ2EclearTimeoutZ_vi)(u32);
void core_clear_timeout(u32 id) {
    pthread_cancel(timer_threads[id].thread);
    timer_threads[id].active = false;
}

void init_core_time() {
    Z_timeZ_coreZ2EsetTimeoutZ_iii = &core_set_timeout;
    Z_timeZ_coreZ2EclearTimeoutZ_vi = &core_clear_timeout;
}
