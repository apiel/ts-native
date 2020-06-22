declare namespace core {
    function cwd(): i32;
}

// export function cwd(): string | null {
//     const ptr = core.cwd();
//     if (ptr) {
//         const len = 12; // need len to fix
//         return changetype<string>(String.UTF8.decodeUnsafe(ptr, len));
//     }
//     return null;
// }
export function cwd(): string {
    const ptr = core.cwd();
    if (ptr) {
        const len = 12; // need len to fix
        return changetype<string>(String.UTF8.decodeUnsafe(ptr, len));
    }
    return '';
}
