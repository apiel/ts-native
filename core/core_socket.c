#include <sys/socket.h>
#include <netinet/in.h> // INADDR_ANY

#include "./lib.h"

u32 (*Z_socketZ_coreZ2Ecreate_socketZ_iv)();
u32 core_create() {
    int32_t socket_id = socket(AF_INET, SOCK_STREAM, 0);
    return socket_id;
}

u32 (*Z_socketZ_coreZ2Elisten_socketZ_iiii)(u32, u32, u32);
u32 core_listen(u32 socket_id, u32 port, u32 long_ip) {
    struct sockaddr_in addr;
    if (long_ip) {
        addr.sin_addr.s_addr = long_ip;
    } else {
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    return bind(socket_id, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    // actually here we should create a thread to accept
}

// need close socket

void init_core_socket() {
    Z_socketZ_coreZ2Ecreate_socketZ_iv = &core_create;
    Z_socketZ_coreZ2Elisten_socketZ_iiii = &core_listen;
}
