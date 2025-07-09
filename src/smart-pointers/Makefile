#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./your_program
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O0 -g -fno-omit-frame-pointer
SOURCES = $(wildcard *.c)
EXECUTABLES = $(SOURCES:.c=)
.PHONY: all clean

all: $(EXECUTABLES)

# Pattern rule to compile .c files to executables
%: %.c trampoline-rename.S
	$(CC) $(CFLAGS) -o $@ $^
01-call_stack_highjack-fixed: 01-call_stack_highjack-fixed.c trampoline.S
	$(CC) $(CFLAGS) -o $@ $^
00-call_stack_highjack: 00-call_stack_highjack.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(patsubst %.c,%,$(wildcard *.c))

# Prevent make from treating source files as intermediate files
.PRECIOUS: %.c