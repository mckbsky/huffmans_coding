#include "../headers/tree.h"
#include "../headers/list.h"
#include "../headers/quicksort.h"
#include "../headers/huffman.h"
#include "../headers/histogram.h"
#include "../headers/argument.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **codes;
enum argument arg;

int main(int argc, char **argv) {
  arg = checkArgument(argc, argv);
  clock_t startTime, resultTime;
  startTime = clock();

  if(arg == HELP) {
    printHelp();
    return EXIT_SUCCESS;
  }
  else if(arg == ENCODE || arg == STRING || arg == ALL) {
    double encodeTime = doEncode(argv);
    printf("Compression ratio = %.2lf\n", encodeTime);
  }
  else if(arg == DECODE) {
    doDecode(argv[2], argv[3], argv[4]);
  }
  else if(arg == AUTHORS) {
    printAuthors();
    return EXIT_SUCCESS;
  }
  else if(arg == INVALID) {
    fprintf(stderr, "Incorrect arguments\n");
    return -EINVAL;
  }

  resultTime = clock() - startTime;
  printf("Algorithm took %f seconds.\n",((float)resultTime)/CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}

enum argument checkArgument(int argc, char **argv) {
  if(argc < 2) {
    return HELP;
  }
  else if(argc == 4) {
    if(strcmp(argv[1], "-e") == 0) {
     return ENCODE;
    }
    else if(strcmp(argv[1], "-s") == 0) {
      return STRING;
    }
    else if(strcmp(argv[1], "-a") == 0) {
      return ALL;
    }
  }
  else if(argc == 5) {
    if(strcmp(argv[1], "-d") == 0) {
      return DECODE;
    }
  }
  else if(strcmp(argv[1], "--authors") == 0) {
    return AUTHORS;
  }
  return INVALID;
}

double doEncode(char **argv) {
  int codeCollision = -1;
  struct treeNode histogram[ASCII_TABLE_SIZE];
  struct treeNode *root = NULL;
  double encodeTime;

  if(!createHistogram(argv[2], histogram, arg)) {
    fprintf(stderr, "Error creating histogram\n");
    return -1.0;
  }

  quickSortFreq(histogram, 0, ASCII_TABLE_SIZE - 1);
  root = generateTree(root, histogram);
  if(NULL == root) {
    fprintf(stderr, "Error generating tree\n");
  }
  quickSortChar(histogram, 0, ASCII_TABLE_SIZE - 1);

  createCodeTable(root);

  encodeTime = encode(argv[2], argv[3], histogram, &codeCollision, arg);
  generateKey(histogram, argv[3], codeCollision);

  if(arg == ALL) {
    decode(root, argv[3], "decoded.txt", histogram, &codeCollision);
  }

  freeMemory(root);
  return encodeTime;
}

void createCodeTable(struct treeNode *root) {
  struct listPointers list;
  int i;

  createList(&list);

  codes = (char**)malloc(ASCII_TABLE_SIZE * sizeof(char *));
  for(i = 0; i < ASCII_TABLE_SIZE; i++) {
    codes[i] = NULL;
  }
  createCodes(root, &list);
}

void freeMemory(struct treeNode *root) {
  int i;
  for(i = 0; i < ASCII_TABLE_SIZE; i++) {
    free(codes[i]);
  }
  free(codes);
  removeTree(root);
}

void doDecode(char *input, char *output, char *key) {
  struct treeNode histogram[ASCII_TABLE_SIZE];
  int codeCollision = -1;

  keyToHistogram(key, histogram, &codeCollision);
  quickSortFreq(histogram, 0, ASCII_TABLE_SIZE - 1);

  struct treeNode *root = NULL;
  root = generateTree(root, histogram);
  if(NULL == root) {
    fprintf(stderr, "Error creating tree\n");
    return;
  }

  quickSortChar(histogram, 0, ASCII_TABLE_SIZE - 1);

  decode(root, input, output, histogram, &codeCollision);
  removeTree(root);
}

void printHelp() {
  printf("Huffman's Coding\n");
  printf("Available Commands:\n");
  printf("-e [input] [output] - encodes your input file and saves it to output file\n");
  printf("-s [string] [output] - encodes your string and saves it to output file\n");
  printf("-d [input] [output] [key] - decodes your input file and saves it to output file. It uses key generated with either '-s' or '-e'\n");
  printf("-a [input] [output] - perform encoding and decoding -- used for debugging purposes\n");
  printf("--authors - prints authors of this application\n");
}

void printAuthors() {
  printf("Authors:\n");
  printf("Maciej Brzeczkowski <maciej.brzeczkowski@protonmail.com>\n");
  printf("Mariusz Lewczuk\n");
}