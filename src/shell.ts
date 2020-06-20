import * as spawn from 'cross-spawn';
import { error } from 'logol';
import { gray, yellow, red } from 'chalk';

export function shell(
    command: string,
    args?: ReadonlyArray<string>,
    cwd = process.cwd(),
    env?: NodeJS.ProcessEnv,
) {
    return new Promise<number>((resolve) => {
        const cmd = spawn(command, args, {
            cwd,
            env: {
                COLUMNS:
                    process.env.COLUMNS || process.stdout.columns.toString(),
                LINES: process.env.LINES || process.stdout.rows.toString(),
                ...env,
                ...process.env,
            },
        });
        cmd.stdout.on('data', (data) => {
            process.stdout.write(gray(data.toString()));
        });
        cmd.stderr.on('data', (data) => {
            const dataStr = data.toString();
            if (dataStr.indexOf('warning') !== -1) {
                process.stdout.write(yellow(data.toString()));
            } else {
                process.stdout.write(red(data.toString()));
            }
        });
        // cmd.on('close', (code) => (code ? process.exit(code) : resolve()));
        cmd.on('close', (code) => {
            if (code > 0) {
                error('Watch out, shell command returned an error.');
            }
            resolve(code);
        });
    });
}