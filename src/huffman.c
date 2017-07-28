#include "../headers/tree.h"
#include "../headers/list.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **codes;

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

int main(int argc, char **argv) {
  enum argument arg = checkArgument(argc, argv);
  clock_t startTime, resultTime;
  startTime = clock();

  if(arg == HELP) {
    printHelp();
    return EXIT_SUCCESS;
  }

  if(arg == ENCODE || arg == STRING || arg == ALL) {
    int i;
    int codeCollision = -1;
    struct treeNode histogram[ASCII_TABLE_SIZE];
    char *buffer;

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
      return 0;
    }

    quickSortFreq(histogram, 0, 255);
    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(NULL == root)
      return 0;

    quickSortChar(histogram, 0, 255);

    struct listPointers *list = NULL;
    list = (struct listPointers *)malloc(sizeof(struct listPointers));
    createList(list);

    codes = (char**)malloc(256 * sizeof(char *));
    for(i = 0; i < 256; i++) {
      codes[i] = NULL;
    }
    createCodes(list, root);

    double encodeTime = encode(buffer, argv[3], histogram, &codeCollision);
    printf("Compression ratio = %.2lf\n", encodeTime);

    generateKey(histogram, argv[3], codeCollision);

    if(arg == ALL) {
      resultTime = clock() - startTime;
      printf("Algorithm for -a before decoding took %f seconds.\n",((float)resultTime)/CLOCKS_PER_SEC);
      decode(root, argv[3], "decoded.txt", histogram, &codeCollision);
    }

    for(i = 0; i < 256; i++) {
      free(codes[i]);
    }

    free(codes);
    free(buffer);
    removeTree(root);
    remove("temp.txt");
    resultTime = clock() - startTime;
    printf("Algorithm for your text took %f seconds.\n",((float)resultTime)/CLOCKS_PER_SEC);

  }
  else if(arg == DECODE) {
    startTime = clock();
    doDecode(argv[2], argv[3], argv[4]);
    resultTime = clock() - startTime;
    printf("Algorithm for decoding your text took %f seconds.\n",((float)resultTime)/CLOCKS_PER_SEC);
  }
  else if(arg == AUTHORS) {
    printAuthors();
    return EXIT_SUCCESS;
  }
  else {
    fprintf(stderr, "Incorrect arguments\n");
    return -EINVAL;
  }

  return 0;
}
