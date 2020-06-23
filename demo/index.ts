import { print } from '../std/io';
import { cwd } from '../std/core';

export function main(argsRef: i32, argsCounts: i32): i32 {
    print('cwd ' + cwd() + '\n');
    print(`Hello world\n`);
    return 0;
}
