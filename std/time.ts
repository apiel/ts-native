declare namespace core {
    function setTimeout(cb: () => void, ms: i32): i32;
    function clearTimeout(id: i32): void;
}

export function setTimeout(cb: () => void, ms: i32): i32 {
    return core.setTimeout(cb, ms);
}

export function clearTimeout(id: i32): void {
    core.clearTimeout(id);
}
