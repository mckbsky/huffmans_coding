#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Tree.hpp"
#include <vector>

class Huffman {

public:

    static int ASCII_TABLE_SIZE;

    void printHelp();

    void printAuthors();

    enum Argument checkArgument(int argc, char **argv);

    void doDecode(char *input, char *output, char *key);

    void freeMemory(Tree *tree);

    std::vector<char> doEncode(const char *input, const char *output, Argument arg);
};


#endif