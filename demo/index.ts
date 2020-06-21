// The entry file of your WebAssembly module.

declare namespace core {
    function abc(val: i32): void;
    function print(ptr: usize, len: i32): void;
}

function print(str: string): void {
    core.print(
        changetype<usize>(String.UTF8.encode(str)),
        String.UTF8.byteLength(str),
    );
}

export function main(a: i32, b: i32): i32 {
    core.abc(a);
    // core.print(`Hello world\n`);
    print(`Hello world\n`);
    return a + b;
}
