// The entry file of your WebAssembly module.

declare namespace core {
    function abc(val: i32): i32;
    function print(ptr: usize, len: i32): void;
}

function print(str: string): void {
    core.print(
        changetype<usize>(String.UTF8.encode(str)),
        String.UTF8.byteLength(str),
    );
}

export function main(a: i32, b: i32): i32 {
    const abc = core.abc(a);
    print('abc ret ' + abc.toString() + '\n');
    const str = changetype<string>(String.UTF8.decodeUnsafe(abc, 12));
    print('try ' + str + '\n');
    print('\n');
    // core.print(`Hello world\n`);
    print(`Hello world\n`);
    return a + b;
}
