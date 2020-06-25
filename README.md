# ts-native

Ts-native is a wrapper around [AssemblyScript](https://www.assemblyscript.org/) and [wasm2c](https://github.com/WebAssembly/wabt/tree/master/wasm2c) to generate some native applications from TypeScript.

AssemblyScript is a an active project, with a big community around, so seem to be the right project to build a tool. All the TS logic is handle by AssemblyScript and all the memory management base on WebAssembly. Finally, `wasm2c` from `wabt` was build by the WebAssembly team, therefor seem to reliable tool to convert wasm files to C. Ts-native is simply putting all those tools together and bring some extra interface to access native feature like file system manipulation or creating some TCP communication...

The way it work is pretty simple, it first compile TypeScript to WASM with AssemblyScript, then WASM to C with wasm2c and finally from C to native machine code with gcc.

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

The TypeScript syntax is tight to AssemblyScript and differ a little but from NodeJs implementation.

> The first peculiarity one is going to notice when writing AssemblyScript is that its [basic types](https://www.assemblyscript.org/types.html) are a bit different from TypeScript's in that it uses WebAssembly's more specific integer and floating point types, with JavaScript's number merely an alias of WebAssembly's f64.

Run the compiler:

```sh
npx ts-native ./hello.ts
```

Finally run the application:

```sh
./build/main
```

## Standard library

AssemblyScript is only providing basic TypeScript logic but doesn't provide any feature to access native feature from the system. To solve this ts-native is providing a standard library:

### ts-native/core

```ts
// return the current working directory
function cwd(): string;
```

### ts-native/io

```ts
// print string to stdout
function print(str: string): void;
```

### ts-native/time

```ts
// calls a function or evaluates an expression after a specified number of milliseconds.
function setTimeout(cb: () => void, ms: i32): i32;
// clears a timer set with the setTimeout() method.
function clearTimeout(id: i32): void;
```
