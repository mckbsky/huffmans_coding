#include "../headers/tree.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct treeNode* addLeaf(struct treeNode *histogram, int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->c = histogram[index].c;
  return node;
}

struct treeNode* addTwoLeaves(struct treeNode *histogram, int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left->c = histogram[index - 1].c;
  node->right = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->right->c = histogram[index].c;
  return node;
}

struct treeNode* addLeafToLeftBranch(struct treeNode *histogram,
                                     struct treeNode *root, int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left->c = histogram[index].c;
  node->right = root;
  return node;
}

struct treeNode* addTwoLeavesAndCreateNewRoot(struct treeNode *histogram,
                                              struct treeNode *root,
                                              int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left->c = histogram[index - 1].c;
  node->right = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->right->c = histogram[index].c;

  struct treeNode *newRoot = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  newRoot->left = node;
  newRoot->right = root;
  return newRoot;
}

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram) {
  int index = findHistogramSize(histogram);

  while(index >= 0) {
    if(NULL == root) {
      if(index == 0) {
        root = addLeaf(histogram, index);
      }
      else {
        root = addTwoLeaves(histogram, index);
      }
    }
    else if(NULL != root) {
      if(index == 0) {
        root = addLeafToLeftBranch(histogram, root, index);
      }
      else {
        root = addTwoLeavesAndCreateNewRoot(histogram, root, index);
      }
    }
    index -= NUMBER_OF_NODES;
  }
  return root;
}

void createCodes(struct treeNode *root, struct listPointers *list) {
  if(isSingleLeafTree(root, list)) {
    insertListNode(list);
    list->head->code = CODE_LEFT;
  }

  if(isLeaf(root)) {
    saveCode(list, root->c);
    deleteListNode(&list);
    return;
  }

  insertListNode(list);
  list->head->code = CODE_RIGHT;
  createCodes(root->right, list);
  insertListNode(list);
  list->head->code = CODE_LEFT;
  createCodes(root->left, list);
  deleteListNode(&list);
}

bool isSingleLeafTree(struct treeNode *root, struct listPointers *list) {
  return root->left == NULL && root->right == NULL && list->head == list->tail;
}

bool isLeaf(struct treeNode *root) {
  return root->c != 0;
}

void saveCode(struct listPointers *list, unsigned char c) {
  struct listNode *tmp = list->tail->prev;
  unsigned int i;
  size_t allocatedChunks = 0;

  for(i = 0; tmp != NULL; i++) {
    if(i + 2 >= allocatedChunks) {
      allocatedChunks += 10;
      codes[c] = (char *)realloc(codes[c], (allocatedChunks) * sizeof(char));
    }
    codes[c][i] = tmp->code;
    codes[c][i + 1] = '\0';
    tmp = tmp->prev;
  }
}

double encode(char *inputFileName, char *outputFileName,
              struct treeNode *histogram, int *codeCollision,
              enum argument arg) {
  FILE *inputFile = NULL;
  FILE *outputFile = fopen(outputFileName, "wb");
  long inputFileSize = 0, outputFileSize = 0;

  if(arg == ENCODE || arg == ALL) {
    inputFile = fopen(inputFileName, "r");
  }
  else if(arg == STRING) {
    inputFile = fmemopen((void *)inputFileName, strlen(inputFileName), "r");
  }
  else {
    return -EINVAL;
  }

  if(inputFile == NULL) {
    fprintf(stderr, "Error: Can't open input file - %s\n", inputFileName);
    return -EIO;
  }
  if(outputFile == NULL) {
    fprintf(stderr, "Error: Can't open output file - %s\n", outputFileName);
    return -EIO;
  }

  int i = 1;
  int j = 0;

  unsigned char parsedChar;
  unsigned char byte[BYTE_SIZE + 1] = {0};

  while(fscanf(inputFile,"%c", &parsedChar) == 1) {
    if(!IS_ASCII(parsedChar)) {
      fprintf(stderr, "Found non-ASCII character -> %c (%d), exiting... ", parsedChar, parsedChar);
      return -1.0;
    }
    inputFileSize++;
    while(true) {
      if(codes[parsedChar][j] != '\0') {
        byte[i - 1] = codes[parsedChar][j];
        i++; j++;
      }
      else {
        if(fscanf(inputFile,"%c", &parsedChar) == 1) {
          inputFileSize++;
          j = 0;
        }
        else {
          break;
        }
      }
      if (i > BYTE_SIZE) {
        unsigned char tmp = binToAscii(byte, histogram, codeCollision);
        fwrite(&tmp, 1, 1, outputFile);
        outputFileSize++;
        memset(byte, 0, sizeof(byte));
        i = 1;
        continue;
      }
    }
    if(i < BYTE_SIZE) {
      unsigned char tmp = binToAscii(byte, histogram, codeCollision);
      fwrite(&tmp, 1, 1, outputFile);
      outputFileSize++;
    }
  }

  if(fclose(inputFile)) {
    fprintf(stderr, "Error: can't close input file - encode()\n");
  }
  if(fclose(outputFile)) {
    fprintf(stderr, "Error: can't close output file - encode()\n");
  }

  printf("Encoding of [%s] successful!\n", inputFileName);
  return (double)outputFileSize / inputFileSize;
}

unsigned char binToAscii(unsigned char *binary, struct treeNode *histogram,
                         int *codeCollision) {
  int i, j;
  int zeroes = 0;
  unsigned char ascii = 0;

  for(i = 0; binary[i + 1] != '\0'; ++i);

  for(j = 0; i >= 0; --i) {
    if(binary[i] == '1') {
      ascii += pow(2, j);
    }
    j += 1;
  }

  for(j = 0; binary[j] == '0'; ++j) {
    zeroes += 1;
  }

  if(zeroes != 0 && histogram[ascii].zeroes == 0) {
    histogram[ascii].zeroes = zeroes;
  } else if(histogram[ascii].zeroes != zeroes){
    *codeCollision = zeroes;
  }
  return ascii;
}

void generateKey(struct treeNode *histogram, char *outputFile,
                 int codeCollision) {

  const char* postfix = "_key";
  char *keyFileName = (char*)malloc(strlen(outputFile) + strlen(postfix));

  strcpy(keyFileName, outputFile);
  strcat(keyFileName, postfix);

  FILE *file = fopen(keyFileName, "w");

  if(file == NULL) {
    fprintf(stderr, "Error: Can't open input file - %s\n", keyFileName);
    return;
  }

  fprintf(file, "%d:", codeCollision);
  int i;
  for(i = 0; i < ASCII_TABLE_SIZE; ++i) {
    if (histogram[i].freq != 0 || histogram[i].zeroes != 0)
      fprintf(file, "%d:%d:%d:", histogram[i].c, histogram[i].freq, histogram[i].zeroes);
  }
  printf("Your decoding key was saved to: [%s]\n", keyFileName);

  if(fclose(file)) {
    fprintf(stderr, "Error: can't close input file - encode()\n");
  }

  free(keyFileName);
}

void keyToHistogram(char *keyFileName, struct treeNode *histogram, int *codeCollision) {
  char *token;
  char *key;

  prepareHistogram(histogram);

  FILE *file = fopen(keyFileName, "r");
  if(file == NULL) {
    fprintf(stderr, "Error: Can't open key file - %s\n", keyFileName);
    return;
  }

  int keyFileSize = fileSize(file);
  key = (char *)malloc(keyFileSize);

  int i = 0;
  char buffer;
  while(fread(&buffer, 1, 1, file) == 1) {
    key[i++] = buffer;
  }

  const char* delimeter = ":";

  token = strtok(key, delimeter);
  *codeCollision = atoi(token);
  token = strtok(NULL, delimeter);
  while (token != NULL) {
    i = atoi(token);
    token = strtok(NULL, delimeter);
    histogram[i].freq = atoi(token);
    token = strtok(NULL, delimeter);
    histogram[i].zeroes = atoi(token);
    token = strtok(NULL, delimeter);
  }

  if(fclose(file)) {
    fprintf(stderr, "Error: can't close key file - %s\n", keyFileName);
  }

  free(key);
}

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *codeCollision) {
  struct treeNode *tmp = root;
  FILE *iFile, *oFile;
  unsigned char buffer;
  unsigned char buffer_arr[9];
  int i;
  int file_size;
  memset(buffer_arr, 0, sizeof(buffer_arr));
  iFile = fopen(inputFile, "rb");
  oFile = fopen(outputFile, "w");

  if(iFile == NULL) {
    fprintf(stderr, "Error: Can't open input file - decode()\n");
  }
  if(oFile == NULL) {
    fprintf(stderr, "Error: Can't open output file - decode()\n");
  }

  fseek(iFile, 0, SEEK_END);
  file_size = ftell(iFile);
  fseek(iFile, 0, SEEK_SET);

  while(fread(&buffer, 1, 1, iFile) == 1) {
    if(ftell(iFile) == file_size && *codeCollision != -1) {
      histogram[buffer].zeroes = *codeCollision;
    }
    asciiToBin(buffer, buffer_arr, histogram);
      for(i = 0; buffer_arr[i] != '\0'; i++) {
        if(buffer_arr[i] == '0' && tmp->left != NULL) {
          tmp = tmp->left;
        }
        else if(buffer_arr[i] == '1' && tmp->right != NULL) {
          tmp = tmp->right;
        }
        if(tmp->left == NULL && tmp->right == NULL) {
          fprintf(oFile, "%c", tmp->c);
          tmp = root;
        }
      }
      memset(buffer_arr, 0, sizeof(buffer_arr));
  }
  if(fclose(iFile))
    fprintf(stderr, "Error: Can't close input file - decode()\n");
  if(fclose(oFile))
    fprintf(stderr, "Error: Can't close output file - decode()\n");

  printf("Decoding of file [%s] successful!\n", inputFile);
}

void asciiToBin(unsigned char ascii, unsigned char *binary, struct treeNode *histogram) {
  int i;
  int j = 0;
  int zeroes = histogram[ascii].zeroes;

  for(i = BYTE_SIZE - 1; ascii != 0; --i) {
    if((ascii & 1) == 0) {
        binary[i] = '0';
    }
    else {
      binary[i] = '1';
    }
    ascii >>= 1;
  }
  i += 1;

  if(i != 0) {
    if(zeroes > 0) {
      for(; zeroes > 0; --zeroes) {
        binary[(i--) - 1] = '0';
      }
    }

    while(binary[i] != '\0') {
      binary[j++] = binary[i++];
    }
    binary[j] = '\0';
  }
}

void removeTree(struct treeNode *root) {
  if(root->left == NULL && root->right == NULL) {
    free(root);
    root = NULL;
    return;
  }
  removeTree(root->right);
  if(root->left != NULL) {
    removeTree(root->left);
  }
  free(root);
}
