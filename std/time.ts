declare namespace core {
    function setTimeout(cb: () => void, ms: i32): i32;
}

export function setTimeout(cb: () => void, ms: i32): i32 {
    return core.setTimeout(cb, ms);
}
