CC = gcc
CFLAGS = -Wall -g -I../

SRCS = ../utz.c ../zones.c test_offsets.c

test: test_offsets
	./test_offsets

test_offsets: $(SRCS) ../utz.h ../zones.h
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f test_offsets

.PHONY: test clean
