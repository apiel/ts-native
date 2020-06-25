"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.shell = void 0;
const spawn = require("cross-spawn");
const logol_1 = require("logol");
const chalk_1 = require("chalk");
function shell(command, args, cwd = process.cwd(), env) {
    return new Promise((resolve) => {
        const cmd = spawn(command, args, {
            cwd,
            env: Object.assign(Object.assign({ COLUMNS: process.env.COLUMNS || process.stdout.columns.toString(), LINES: process.env.LINES || process.stdout.rows.toString() }, env), process.env),
        });
        cmd.stdout.on('data', (data) => {
            process.stdout.write(chalk_1.gray(data.toString()));
        });
        cmd.stderr.on('data', (data) => {
            const dataStr = data.toString();
            if (dataStr.indexOf('warning') !== -1) {
                process.stdout.write(chalk_1.yellow(data.toString()));
            }
            else {
                process.stdout.write(chalk_1.red(data.toString()));
            }
        });
        cmd.on('close', (code) => {
            if (code > 0) {
                logol_1.error('Watch out, shell command returned an error.');
            }
            resolve(code);
        });
    });
}
exports.shell = shell;
//# sourceMappingURL=shell.js.map