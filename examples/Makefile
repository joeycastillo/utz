CC = gcc
CFLAGS = -Wall -g -I../

TARGET = example

SRCS = ../utz.c ../zones.c utility.c example.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

example.o: ../utz.h ../zones.h

clean:
	rm -f $(OBJS) $(TARGET)
