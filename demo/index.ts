import { print } from '../std/io';
import { cwd } from '../std/core';

export function main(a: i32, b: i32): i32 {
    print('cwd ' + cwd() + '\n');
    print(`Hello world\n`);
    return a + b;
}
