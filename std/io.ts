declare namespace core {
    function print(ptr: usize, len: i32): void;
}

export function print(str: string): void {
    core.print(
        changetype<usize>(String.UTF8.encode(str)),
        String.UTF8.byteLength(str),
    );
}
