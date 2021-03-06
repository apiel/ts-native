declare namespace core {
    function cwd(): i32;
}

export function cwd(): string {
    let ptr = core.cwd();
    if (ptr) {
        let len = <u32>load<u8>(ptr);
        ptr++;
        return changetype<string>(String.UTF8.decodeUnsafe(ptr, len));
    }
    return '';
}
