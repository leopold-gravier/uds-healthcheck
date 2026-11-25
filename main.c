/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


char const* const help_str = 
"Usage: uds-healthcheck -s [SOCK_PATH]\n" \
"Checks that a Unix-domain socket is responding.\n" \
"\n" \
"Options:" \
"    -h | --help   \tDisplay this documentation message and exit\n" \
"    -s | --socket \tThe path of the socket to connect to\n" \
"    -v | --version\tDisplay the version and license information and exit";

char const* const version_str = 
"uds-healthcheck v1.0.0\n" \
"\n" \
"License MPL 2.0: free to use and redistribute, modifications must be shared.\n" \
"There is NO WARRANTY, to the extent permitted by law.\n" \
"\n" \
"Written by Léopold Gravier\n" \
"The source code is available at https://github.com/leopold-gravier/uds-healthcheck.";

char const* const usage_str =
"Usage: uds-healthcheck -s [SOCK_PATH]\n";


static int perform_healthcheck(char const* sock_path) {
    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, sock_path, sizeof(addr.sun_path)-1);
    addr.sun_path[sizeof(addr.sun_path)-1] = 0;
    
    int ret = connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret != 0) {
        perror("connect");
        return 1;
    }

    ret = close(sock_fd);
    if (ret != 0) {
        perror("close");
        return 1;
    }

    return 0;
}

int main(int argc, char** argv) {
    char const* sock_path = NULL;

    for (int arg_id=1; arg_id < argc; arg_id += 1) {
        char const* arg = argv[arg_id];
        if ((strcmp(arg, "-h") == 0) || (strcmp(arg, "--help") == 0)) {
            puts(help_str);
            return 0;
        } else if ((strcmp(arg, "-s") == 0) || (strcmp(arg, "--socket") == 0)) {
            if (sock_path != NULL) {
                fputs("Argument -s can only be used once\n", stderr);
                return 1;
            }

            arg_id += 1;
            sock_path = argv[arg_id];
        } else if ((strcmp(arg, "-v") == 0) || (strcmp(arg, "--version") == 0)) {
            puts(version_str);
            return 0;
        } else {
            fprintf(stderr, "Unknown argument: %s\n%s", arg, usage_str);
            return 1;
        }
    }

    if (sock_path == NULL) {
        fprintf(stderr, "Missing required argument -s\n%s", usage_str);
        return 1;
    } else {
        return perform_healthcheck(sock_path);
    }
}
