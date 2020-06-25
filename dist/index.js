"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const process_1 = require("process");
const path_1 = require("path");
const logol_1 = require("logol");
const fs_1 = require("fs");
const shell_1 = require("./shell");
const [, , file] = process_1.argv;
const entryPoint = path_1.join(process_1.cwd(), file);
logol_1.log('entryPoint:', entryPoint);
const buildFolder = path_1.join(process_1.cwd(), 'build');
const tmpFolder = path_1.join(buildFolder, 'tmp');
const wasmFile = path_1.join(tmpFolder, 'lib.wasm');
const cFile = path_1.join(tmpFolder, 'lib.c');
const hFile = path_1.join(tmpFolder, 'lib.h');
const coreFolder = path_1.join(__dirname, '..', 'core');
const binFile = path_1.join(buildFolder, 'main');
const ldFlags = ['-pthread'];
const coreDef = ['Z_coreZ_coreZ', 'Z_ioZ_coreZ', 'Z_timeZ_coreZ'];
start();
function start() {
    return __awaiter(this, void 0, void 0, function* () {
        yield shell_1.shell('asc', `${entryPoint} -b ${wasmFile} --exportTable --sourceMap --optimize`.split(' '));
        yield shell_1.shell('wasm2c', `${wasmFile} -o ${cFile}`.split(' '));
        const cFiles = copyCore();
        const defines = getDefines();
        yield shell_1.shell('cc', [...ldFlags, ...defines, '-o', binFile, cFile, ...cFiles], tmpFolder);
        if (!process_1.argv.includes('--skip-rm')) {
            fs_1.rmdirSync(tmpFolder, { recursive: true });
        }
    });
}
function getDefines() {
    let defines = [];
    const hContent = fs_1.readFileSync(hFile).toString();
    coreDef.forEach((def) => {
        if (hContent.includes(def)) {
            defines = [...defines, '-D', `INC_${def.toUpperCase()}`];
        }
    });
    logol_1.log('defines:', defines);
    return defines;
}
function copyCore() {
    const files = fs_1.readdirSync(coreFolder);
    const cFiles = [];
    files.forEach((file) => {
        if (path_1.extname(file) === '.c') {
            cFiles.push(file);
        }
        fs_1.copyFileSync(path_1.join(coreFolder, file), path_1.join(tmpFolder, file));
    });
    return cFiles;
}
//# sourceMappingURL=index.js.map