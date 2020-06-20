import { argv, cwd } from 'process';
import { join } from 'path';
import { log } from 'logol';
import { readdirSync, copyFileSync } from 'fs';

import { shell } from './shell';

const [, , file] = argv;
const entryPoint = join(cwd(), file);
log('entryPoint:', entryPoint);

const buildFolder = join(cwd(), 'build');
const tmpFolder = join(buildFolder, 'tmp');
const wasmFile = join(tmpFolder, 'lib.wasm');
const wasmFolder = join(__dirname, '..', 'wasm');

start();

async function start() {
    await shell(
        'asc',
        `${entryPoint} -b ${wasmFile} --sourceMap --optimize`.split(' '),
    );
    copyWasm();
}

function copyWasm() {
    const files = readdirSync(wasmFolder);
    files.forEach(file => {
        copyFileSync(join(wasmFolder, file), join(tmpFolder, file));
    });
}
