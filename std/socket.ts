declare namespace core {
    function create_socket(): i32;
    function listen_socket(socketId: u32, port: u32, longIp: u32): i32;
}

export function create(): i32 {
    return core.create_socket();
}

// 127.0.0.1 = 2130706433
export function listen(socketId: u32, port: u32, longIp: u32 = 0): i32 {
    return core.listen_socket(socketId, port, longIp);
}

// need close socket
