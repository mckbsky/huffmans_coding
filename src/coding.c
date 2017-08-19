#include "../headers/coding.h"
#include "../headers/tree.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

void decode(struct treeNode *root, char *inputFileName, char *outputFileName, struct treeNode *histogram, int *codeCollision) {
  struct treeNode *tmp = root;
  FILE *inputFile, *outputFile;

  inputFile = fopen(inputFileName, "rb");
  outputFile = fopen(outputFileName, "w");

  if(inputFile == NULL) {
    fprintf(stderr, "Error: Can't open input file - %s\n", inputFileName);
  }
  if(outputFile == NULL) {
    fprintf(stderr, "Error: Can't open output file - %s\n", outputFileName);
  }

  int inputFileSize;
  inputFileSize = fileSize(inputFile);

  unsigned char parsedChar;
  unsigned char binary[BYTE_SIZE + 1] = {0};
  while(fread(&parsedChar, 1, 1, inputFile) == 1) {
    if(ftell(inputFile) == inputFileSize && *codeCollision != -1) {
      histogram[parsedChar].zeroes = *codeCollision;
    }
    asciiToBin(parsedChar, binary, histogram);
    int i;
    for(i = 0; binary[i] != '\0'; ++i) {
      if(binary[i] == '0' && tmp->left != NULL) {
        tmp = tmp->left;
      }
      else if(binary[i] == '1' && tmp->right != NULL) {
        tmp = tmp->right;
      }
      if(tmp->left == NULL && tmp->right == NULL) {
        fprintf(outputFile, "%c", tmp->c);
        tmp = root;
      }
    }
    memset(binary, 0, sizeof(binary));
  }

  if(fclose(inputFile))
    fprintf(stderr, "Error: Can't close input file - %s\n", outputFileName);
  if(fclose(outputFile))
    fprintf(stderr, "Error: Can't close output file - %s\n", outputFileName);

  printf("Decoding of file [%s] successful!\n", inputFileName);
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