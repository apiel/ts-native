import { print } from '../std/io';
import { cwd } from '../std/core';
import { setTimeout } from '../std/time';

export { event} from '../std/event';

// function cb(): void {
//     print('callback\n');
// }

export function main(argc: i32, argsRef: i32): i32 {
    print('cwd ' + cwd() + '\n');
    print(`Hello world\n`);
    // iprint(cb);

    setTimeout(function cb() {
        print(`setTimeout cb\n`);
    }, 1000);

    return 0;
}
