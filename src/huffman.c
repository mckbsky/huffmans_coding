#include "../headers/tree.h"
#include "../headers/list.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **codes;
enum argument arg;

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

enum argument {
  ENCODE, DECODE, STRING, ALL, HELP, AUTHORS, INVALID
};

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

void doEncode(char **argv) {
    int codeCollision = -1;
    struct treeNode histogram[ASCII_TABLE_SIZE];
    struct listPointers *list = NULL;
    char *buffer;
    int i;

    if(arg == STRING) {
      FILE *file;
      file = fopen("temp.txt", "w");
      while(fprintf(file, "%s", argv[2]) == 1);
      buffer = (char *)malloc(strlen("temp.txt"));
      strcpy(buffer, "temp.txt");
      fclose(file);
    }
    else {
      buffer = (char *)malloc(strlen(argv[2]));
      strcpy(buffer, argv[2]);
    }

    if(!createHistogram(buffer, histogram)) {
      fprintf(stderr, "Error creating histogram\n");
      return;
    }

    quickSortFreq(histogram, 0, ASCII_TABLE_SIZE - 1);
    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(NULL == root) {
      fprintf(stderr, "Error generating tree\n");
    }

    quickSortChar(histogram, 0, ASCII_TABLE_SIZE - 1);

    list = (struct listPointers *)malloc(sizeof(struct listPointers));
    createList(list);

    codes = (char**)malloc(ASCII_TABLE_SIZE * sizeof(char *));
    for(i = 0; i < ASCII_TABLE_SIZE; i++) {
      codes[i] = NULL;
    }
    createCodes(list, root);

    double encodeTime = encode(buffer, argv[3], histogram, &codeCollision);
    printf("Compression ratio = %.2lf\n", encodeTime);

    generateKey(histogram, argv[3], codeCollision);

    if(arg == ALL) {
      decode(root, argv[3], "decoded.txt", histogram, &codeCollision);
    }

    for(i = 0; i < ASCII_TABLE_SIZE; i++) {
      free(codes[i]);
    }

    free(codes);
    free(buffer);
    removeTree(root);
    remove("temp.txt");
}

int main(int argc, char **argv) {
  arg = checkArgument(argc, argv);
  clock_t startTime, resultTime;
  startTime = clock();

  if(arg == HELP) {
    printHelp();
    return EXIT_SUCCESS;
  }
  else if(arg == ENCODE || arg == STRING || arg == ALL) {
    doEncode(argv);
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
