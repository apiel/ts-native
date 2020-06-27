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

const ldFlags = ['-pthread'];
const coreDef = ['Z_coreZ_coreZ', 'Z_ioZ_coreZ', 'Z_timeZ_coreZ', 'Z_socketZ_coreZ'];

start();

async function start() {
    await shell(
        'asc',
        `${entryPoint} -b ${wasmFile} --exportTable --optimize`.split(' '), // -t lib.wat
    );
    await shell('wasm2c', `${wasmFile} -o ${cFile}`.split(' '));
    const cFiles = copyCore();
    const defines = getDefines();
    await shell('cc', [...ldFlags, ...defines, '-o', binFile, cFile, ...cFiles], tmpFolder);
    if (!argv.includes('--skip-rm')) {
        rmdirSync(tmpFolder, { recursive: true });
    }
}

function getDefines() {
    let defines = [];
    const hContent = readFileSync(hFile).toString();
    coreDef.forEach((def) => {
        if (hContent.includes(def)) {
            defines = [...defines, '-D', `INC_${def.toUpperCase()}`];
        }
    });
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
