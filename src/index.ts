import { argv, cwd } from 'process';
import { join, extname } from 'path';
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
const coreFolder = join(__dirname, '..', 'core');
const binFile = join(buildFolder, 'main');

start();

async function start() {
    await shell(
        'asc',
        `${entryPoint} -b ${wasmFile} --sourceMap --optimize`.split(' '),
    );
    await shell('wasm2c', `${wasmFile} -o ${cFile}`.split(' '));
    const cFiles = copyCore();
    await shell('cc', ['-o', binFile, cFile, ...cFiles], tmpFolder);
    if (!argv.includes('--skip-rm')) {
        rmdirSync(tmpFolder, { recursive: true });
    }
}

function copyCore() {
    const files = readdirSync(coreFolder);
    const cFiles = [];
    files.forEach((file) => {
        if (extname(file) === '.c') {
            cFiles.push(file);
        }
        copyFileSync(join(coreFolder, file), join(tmpFolder, file));
    });
    return cFiles;
}
