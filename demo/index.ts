import { print } from '../std/io';
import { cwd } from '../std/core';
import { setTimeout, clearTimeout } from '../std/time';

// function cb(): void {
//     print('callback\n');
// }

// ToDo: args
export function main(argc: i32, argsRef: i32): i32 {
    print('cwd ' + cwd() + '\n');
    print(`Hello world\n`);
    // iprint(cb);

    const id = setTimeout(function cb() {
        print(`setTimeout cb\n`);
    }, 2000);
    print(`after setTimeout\n`);
    // clearTimeout(id);

    return 0;
}
