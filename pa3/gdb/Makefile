# tools
CC := gcc
RM := rm -f

# flags
CFLAGS := -ggdb -m32 -static

default: all

all: fib.c
	$(CC) $(CFLAGS) fib.c -o fib

clean:
	$(RM) fib *.o
