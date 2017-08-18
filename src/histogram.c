#include "../headers/histogram.h"

int fileSize(FILE* file) {
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);
  return size;
}

void prepareHistogram(struct treeNode *histogram) {
  int i;
  for(i = 0; i < ASCII_TABLE_SIZE; i++) {
    histogram[i].c = i;
    histogram[i].freq = 0;
    histogram[i].zeroes = 0;
  }
}

void fillHistogram(FILE *file, struct treeNode *histogram) {
  char character;
  while(fscanf(file, "%c", &character) == 1) {
    histogram[(int)character].freq++;
  }
}

bool createHistogram(char *inputFile, struct treeNode *histogram,
                     enum argument arg) {
  FILE *file = NULL;

  if(arg == ENCODE || arg == ALL) {
    file = fopen(inputFile, "r");
  }
  else if(arg == STRING) {
    file = fmemopen((void *)inputFile, strlen(inputFile), "r");
  }
  else {
    return false;
  }

  if(NULL == file) {
    fprintf(stderr, "Error: Can't open input file - createHistogram()\n");
    return false;
  }

  if(fileSize(file) == 0) {
    fprintf(stderr, "Error: empty input file\n");
    return false;
  }

  prepareHistogram(histogram);
  fillHistogram(file, histogram);

  if(fclose(file)) {
    fprintf(stderr, "Error: Can't close input file - createHistogram()\n");
    return false;
  }

  return true;
}

int findHistogramSize(struct treeNode *histogram) {
  int size;
  for(size = 0; size < ASCII_TABLE_SIZE; ++size) {
    if(histogram[size + 1].freq == 0)
      return size;
  }
  return 0;
}