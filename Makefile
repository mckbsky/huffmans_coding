CC=clang
CFLAGS=-Wall -Wextra -O2
SRC=$(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: huffman

huffman: $(OBJ)
	$(CC) -o $@ $^ -lm

clear:
	rm $(OBJ)
