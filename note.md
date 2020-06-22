- need docker
- ? xxd -i build/tmp/lib.wasm

- rs:
```sh
bindgen lib.h -o lib.rs
```
main.rs
```rs
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!("lib.rs");

fn main() {
    unsafe {
        init();
    }
}
```
Cargo.toml
```toml
[package]
name = "main"
version = "0.0.1"
edition = "2018"
default-run = "main"

[[bin]]
name = "main"
path = "main.rs"
```