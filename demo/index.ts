import { print } from '../std/io';
import { cwd } from '../std/core';

export function main(argc: i32, argsRef: i32): i32 {
    print('cwd ' + cwd() + '\n');
    print(`Hello world\n`);
    return 0;
}
