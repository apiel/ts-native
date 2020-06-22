import { argv, cwd } from 'process';
import { join } from 'path';
import { log } from 'logol';
import { readdirSync, copyFileSync, rmdirSync } from 'fs';

import { shell } from './shell';

const [, , file] = argv;
const entryPoint = join(cwd(), file);
log('entryPoint:', entryPoint);

const buildFolder = join(cwd(), 'build');
const tmpFolder = join(buildFolder, 'tmp');
const wasmFile = join(tmpFolder, 'lib.wasm');
const cFile = join(tmpFolder, 'lib.c');
const wasmFolder = join(__dirname, '..', 'wasm');
const binFile = join(buildFolder, 'main');

start();

async function start() {
    await shell(
        'asc',
        `${entryPoint} -b ${wasmFile} --sourceMap --optimize`.split(' '),
    );
    await shell('wasm2c', `${wasmFile} -o ${cFile}`.split(' '));
    copyWasm();
    await shell(
        'cc',
        `-o ${binFile} main.c lib.c wasm-rt-impl.c`.split(' '),
        tmpFolder,
    );
    if (!argv.includes('--skip-rm')) {
        rmdirSync(tmpFolder, { recursive: true });
    }
}

function copyWasm() {
    const files = readdirSync(wasmFolder);
    files.forEach((file) => {
        copyFileSync(join(wasmFolder, file), join(tmpFolder, file));
    });
}
