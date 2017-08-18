#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "../headers/argument.h"

void printHelp();
void printAuthors();
enum argument checkArgument(int argc, char **argv);
void doDecode(char *input, char *output, char *key);
void freeMemory(struct treeNode *root);
void createCodeTable(struct treeNode *root);
double doEncode(char **argv);

#endif