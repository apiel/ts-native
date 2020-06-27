#include <arpa/inet.h>   // inet_ntoa
#include <netinet/in.h>  // INADDR_ANY
#include <pthread.h>
#include <stdbool.h>  // bool
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc
#include <sys/socket.h>
#include <unistd.h>  // close

#include "./lib.h"

#ifndef MAX_SERVER_COUNT
#define MAX_SERVER_COUNT 10
#endif

struct server_thread {
    pthread_t thread;
    bool active;
    u32 socket_id;
};

struct server_thread server_threads[MAX_SERVER_COUNT];

int8_t get_free_server_thread_index() {
    for (uint8_t i = 0; i < MAX_SERVER_COUNT; i++) {
        if (!server_threads[i].active) {
            return i;
        }
    }
    return -1;
}

void join_servers() {
    for (uint8_t i = 0; i < MAX_SERVER_COUNT; i++) {
        if (server_threads[i].active) {
            pthread_join(server_threads[i].thread, NULL);
        }
    }
}

static void *server(void *id_ptr) {
    int8_t id = *((int *)id_ptr);
    struct sockaddr_in remote_addr;
    int sin_size;
    int remote_socket_id;

    printf("start server\n");
    while (1) { /* main accept() loop */
        sin_size = sizeof(struct sockaddr_in);
        if ((remote_socket_id =
                 accept(server_threads[id].socket_id,
                        (struct sockaddr *)&remote_addr, &sin_size)) == -1) {
            printf("Failed to create new connection\n");
        }
        printf("server: got connection from %s\n",
               inet_ntoa(remote_addr.sin_addr));
        // if (!fork()) { /* this is the child process */
        //     if (send(remote_socket_id, "Hello, world!\n", 14, 0) == -1)
        //         perror("send");
        //     close(remote_socket_id);
        //     exit(0);
        // }
        // close(remote_socket_id); /* parent doesn't need this */

        // while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    server_threads[id].active = false;
    free(id_ptr);
}

u32 (*Z_socketZ_coreZ2Ecreate_socketZ_iv)();
u32 core_create_socket() { return socket(AF_INET, SOCK_STREAM, 0); }

u32 (*Z_socketZ_coreZ2Elisten_socketZ_iiii)(u32, u32, u32);
u32 core_listen_socket(u32 socket_id, u32 port, u32 long_ip) {
    struct sockaddr_in addr;
    if (long_ip) {
        addr.sin_addr.s_addr = long_ip;
    } else {
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (bind(socket_id, (struct sockaddr *)&addr, sizeof(struct sockaddr)) ==
        -1) {
        return -1;
    }

    if (listen(socket_id, 3) == -1) {
        return -1;
    }

    int8_t id = get_free_server_thread_index();
    if (id != -1) {
        server_threads[id].active = true;
        server_threads[id].socket_id = socket_id;
        int8_t *id_ptr = malloc(sizeof(int8_t));
        *id_ptr = id;
        int err = pthread_create(&server_threads[id].thread, NULL, server,
                                 (void *)id_ptr);
        if (!err) {
            return id;
        } else {
            server_threads[id].active = false;
        }
    }
    return -1;
}

// need close socket
u32 (*Z_socketZ_coreZ2Eclose_socketZ_ii)(u32);
u32 core_close_socket(u32 socket_id) { return close(socket_id); }

void init_core_socket() {
    Z_socketZ_coreZ2Ecreate_socketZ_iv = &core_create_socket;
    Z_socketZ_coreZ2Elisten_socketZ_iiii = &core_listen_socket;
    Z_socketZ_coreZ2Eclose_socketZ_ii = &core_close_socket;
}
