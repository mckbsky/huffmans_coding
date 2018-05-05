#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Tree.hpp"

class Huffman {

private:

    char **codes;

public:

    static int ASCII_TABLE_SIZE;

    void printHelp();

    void printAuthors();

    enum Argument checkArgument(int argc, char **argv);

    void doDecode(char *input, char *output, char *key);

    void freeMemory(Tree *tree);

    void createCodeTable(Tree *tree);

    double doEncode(char **argv, Argument arg);
};


#endif