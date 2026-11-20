# UDS-healthcheck
A small binary to check that a [Unix-domain socket](https://www.man7.org/linux/man-pages/man7/unix.7.html) 
is responding.

## Compile
1. Install dependencies: gcc, make, and libc
2. Clone this repository
3. Run `make` from the root of the repo
4. The binary is available at `build/uds-healthcheck`

## Usage
Run with `uds-healthcheck -s [SOCK_PATH]`. 
Connects to the given socket and immeditely close connection. 
If successful, exits with 0, otherwise exits with 1.

## License
This software is under the MPL 2.0 license.
