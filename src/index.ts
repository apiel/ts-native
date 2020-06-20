import { argv, cwd } from 'process';
import { join } from 'path';
import { shell } from './shell';
import { log } from 'logol';

async function start() {
    const [, , file] = argv;
    const entryPoint = join(cwd(), file);
    log('entryPoint:', entryPoint);

    const buildFolder = join(cwd(), 'build');
    const wasmFile = join(buildFolder, 'tmp', 'lib.wasm');
    await shell(
        'asc',
        `${entryPoint} -b ${wasmFile} --sourceMap --optimize`.split(' '),
    );
}

start();
