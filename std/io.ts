declare namespace core {
    function print(ptr: usize, len: i32): void;
    function print_error(ptr: usize, len: i32): void;
    function iprint(i: i32): void;
}

export function print(str: string): void {
    core.print(
        changetype<usize>(String.UTF8.encode(str)),
        String.UTF8.byteLength(str),
    );
}

export function printError(str: string): void {
    core.print_error(
        changetype<usize>(String.UTF8.encode(str)),
        String.UTF8.byteLength(str),
    );
}

// to be deprecated
export function iprint(i: i32): void {
    core.iprint(i);
}
