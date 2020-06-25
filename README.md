# ts-native

Ts-native is a wrapper around [AssemblyScript](https://www.assemblyscript.org/) and [wasm2c](https://github.com/WebAssembly/wabt/tree/master/wasm2c) to generate some native applications from TypeScript. It first compile TypeScript to WASM, then WASM to C and finally from C to native machine code.

AssemblyScript is a an active project, with a big community around, so seem to be the right project to build a tool. All the TS logic is handle by AssemblyScript and all the memory management base on WebAssembly. Finally, `wasm2c` from `wabt` was build by the WebAssembly team, therefor seem to reliable tool to convert wasm files to C. Ts-native is simply putting all those tools together and bring some extra interface to access native feature like file system manipulation or creating some TCP communication...

> Right now, it is only working on Linux.

## Getting started

First we need install `watb`. On ubuntu add the following line in `/etc/apt/sources.list`

```
deb http://cz.archive.ubuntu.com/ubuntu eoan main universe
```

Then install with apt:

```sh
sudo apt-get update
sudo apt-get install watb
```

We need to install as well gcc and some extra tools:

```sh
sudo apt install build-essential llvm-dev libclang-dev clang
```

Now, we can install ts-native:

```sh
yarn add ts-native
# or
npm install ts-native
```

Let's create an example `hello.ts`:

```ts
import { print } from 'ts-native/io';

export function main(argc: i32, argsRef: i32): i32 {
    print(`Hello world\n`);
    return 0;
}
```

Run the compiler:

```sh
npx ts-native ./hello.ts
```

Finally run the application:

```sh
./build/main
```
