CC=clang
CFLAGS=-Wall -Wextra
OUT=huffman.out
SRC=$(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
OBJDIR=./obj/

all: huffman

huffman: $(OBJ)
	$(CC) -o $@ $^ -lm

clear:
	rm *.o
