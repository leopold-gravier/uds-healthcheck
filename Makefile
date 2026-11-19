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