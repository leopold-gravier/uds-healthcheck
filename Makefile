# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.


CC=gcc
CFLAGS=-O3 -Wall -Werror -fstack-protector -Wl,-z,relro,-z,now -D_FORTIFY_SOURCE=2

all: build/ build/uds-healthcheck

build/uds-healthcheck: main.c
	$(CC) $(CFLAGS) -o $@ $^
	strip $@

build/:
	mkdir $@

.PHONY: clean
clean:
	rm build/*