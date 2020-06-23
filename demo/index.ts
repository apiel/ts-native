import { print } from '../std/io';
import { cwd } from '../std/core';

export { event} from '../std/event';

// function cb(): void {
//     print('callback\n');
// }

export function main(argc: i32, argsRef: i32): i32 {
    print('cwd ' + cwd() + '\n');
    print(`Hello world\n`);
    // iprint(cb);
    return 0;
}
