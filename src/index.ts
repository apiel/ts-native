import { argv, cwd } from 'process';
import { join, extname } from 'path';
import { log } from 'logol';
import { readdirSync, copyFileSync, rmdirSync, readFileSync } from 'fs';

import { shell } from './shell';

const [, , file] = argv;
const entryPoint = join(cwd(), file);
log('entryPoint:', entryPoint);

const buildFolder = join(cwd(), 'build');
const tmpFolder = join(buildFolder, 'tmp');
const wasmFile = join(tmpFolder, 'lib.wasm');
const cFile = join(tmpFolder, 'lib.c');
const hFile = join(tmpFolder, 'lib.h');
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
    const defines = getDefines();
    await shell('cc', [...defines, '-o', binFile, cFile, ...cFiles], tmpFolder);
    if (!argv.includes('--skip-rm')) {
        rmdirSync(tmpFolder, { recursive: true });
    }
}

function getDefines() {
    let defines = [];
    const hContent = readFileSync(hFile).toString();
    if (hContent.includes('Z_coreZ_coreZ')) {
        defines = [...defines, '-D', 'INC_CORE_CORE'];
    }
    if (hContent.includes('Z_ioZ_coreZ')) {
        defines = [...defines, '-D', 'INC_CORE_IO'];
    }
    log('defines:', defines);
    return defines;
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
