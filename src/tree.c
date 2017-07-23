#include "../headers/tree.h"

int fileSize(FILE* file) {
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);
  return size;
}

void prepareHistogram(struct treeNode *histogram) {
  int i;
  for(i = 0; i < ASCII_TABLE_SIZE; i++) {
    histogram[i].c = (char)i;
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

bool createHistogram(char *inputFile, struct treeNode *histogram) {
  FILE *file;
  file = fopen(inputFile, "r");

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

void quickSortChar(struct treeNode *histogram, int begin, int end) {
  int i = begin;
  int j = end;
  int middle;

  middle = histogram[(i + j) / 2].c;

  do {
    while(histogram[i].c < middle) {
      i++;
    }
    while(histogram[j].c > middle) {
      j--;
    }
    if(i <= j) {
      struct treeNode swap = histogram[i];
      histogram[i] = histogram[j];
      histogram[j] = swap;

      i++; j--;
    }
  }
  while(i <=j);

  if(begin < j) {
    quickSortChar(histogram, begin, j);
  }
  if(i < end) {
    quickSortChar(histogram, i, end);
  }
}

void quickSortFreq(struct treeNode *histogram, int begin, int end) {
  int i = begin;
  int j = end;
  int middle = histogram[(i + j) / 2].freq;

  do {
    while(histogram[i].freq > middle) {
      i++;
    }
    while(histogram[j].freq < middle) {
      j--;
    }
    if(i <= j) {
      struct treeNode swap = histogram[i];
      histogram[i] = histogram[j];
      histogram[j] = swap;

      i++; j--;
    }
  }
  while(i <= j);

  if(begin < j) {
    quickSortFreq(histogram, begin, j);
  }
  if(i < end) {
    quickSortFreq(histogram, i, end);
  }
}

int findHistogramSize(struct treeNode *histogram) {
  int size;
  for(size = 0; size < ASCII_TABLE_SIZE; ++size) {
    if(histogram[size + 1].freq == 0)
      return size;
  }
  return 0;
}

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

void createCodes(struct list_pointers *list, struct treeNode *root) {
  if(root->left == NULL && root->right == NULL && list->head == list->tail) {
    insertListNode(list);
    list->head->code = '0';
  }

  if(root->c != 0) {
    saveCode(list, root->c);
    deleteListNode(&list);
    return;
  }

  insertListNode(list);
  list->head->code = '1';
  createCodes(list, root->right);
  insertListNode(list);
  list->head->code = '0';
  createCodes(list, root->left);
  deleteListNode(&list);
}

void saveCode(struct list_pointers *list, unsigned char c) {
  struct list_node *tmp = list->tail->prev;
  unsigned int i;
  for(i = 0; tmp != NULL; i++) {
    codes[(int)c] = (char *)realloc(codes[(int)c], (i + 2) * sizeof(char));
    codes[(int)c][i] = tmp->code;
    codes[(int)c][i + 1] = '\0';
    tmp = tmp->prev;
  }
}

void createList(struct list_pointers *list) {
  struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
  if (new_node != NULL) {
    new_node->code = 2;
    new_node->next = new_node->prev = NULL;
    list->head = list->tail = new_node;
  }
}

void insertListNode(struct list_pointers *list) {
  if(list) {
    struct list_node *new_node = (struct list_node*)malloc(sizeof(struct list_node));
    if(new_node) {
      new_node->prev = NULL;
      new_node->next = list->head;
      list->head->prev = new_node;
      list->head = new_node;
      }
  }
  else {
    fprintf(stderr, "Error: Empty list, can't add new element\n");
  }
}

void deleteListNode(struct list_pointers **list) {
  if((*list)->head == NULL) {
    fprintf(stderr, "Can't delete node from empty list\n");
    return;
  }
  struct list_node* deleted_node = (*list)->head;
  (*list)->head = deleted_node->next;
  free(deleted_node);
}

double encode(char *input, char *outputFile, struct treeNode *histogram, int *double_representation) {
  FILE *iFile, *oFile;
  unsigned char buffer;
  unsigned char buffer_arr[9];
  long iFileSize = 0, oFileSize = 0;
  memset(buffer_arr, 0, sizeof(buffer_arr));
  int i = 1;
  int j = 0;
  iFile = fopen(input, "r");
  oFile = fopen(outputFile, "wb");

  if(iFile == NULL) {
    fprintf(stderr, "Error: Can't open input file - encode()\n");
  }
  if(oFile == NULL) {
    fprintf(stderr, "Error: Can't open output file - encode()\n");
  }

  while(fscanf(iFile,"%c", &buffer) == 1) {
    iFileSize++;
    while(1) {
      if(codes[(int)buffer][j] != '\0') {
        buffer_arr[i - 1] = codes[(int)buffer][j];
        i++; j++;
      }
      else {
        if(fscanf(iFile,"%c", &buffer) == 1) {
          iFileSize++;
          j = 0;
        }
        else {
          break;
        }
      }
      if (i == 9) {
        unsigned char tmp = binToAscii(buffer_arr, histogram, double_representation);
        fwrite(&tmp, 1, 1, oFile);
        oFileSize++;
        memset(buffer_arr, 0, sizeof(buffer_arr));
        i = 1;
        continue;
      }
    }
  }

  if( i != 9) {
    unsigned char tmp = binToAscii(buffer_arr, histogram, double_representation);
    fwrite(&tmp, 1, 1, oFile);
    oFileSize++;
  }

  if(fclose(iFile))
    fprintf(stderr, "Error: can't close input file - encode()\n");
  if(fclose(oFile))
    fprintf(stderr, "Error: can't close output file - encode()\n");

  printf("Encoding of [%s] successful!\n", input);
  return (double)oFileSize / iFileSize;
}

unsigned char binToAscii(unsigned char *binary, struct treeNode *histogram, int *double_representation) {
  int i;
  int j;
  int zeroes = 0;
  unsigned char result = 0;

  for(i = 0; binary[i + 1] != '\0'; i++);

  for(j = 0; i >= 0; i--) {
    if(binary[i] == '1') {
      result += pow(2, j++);
    }
    else {
      j++;
    }
  }
  for(j = 0; binary[j] == '0'; j++) {
    zeroes++;
  }
  if(zeroes != 0 && histogram[result].zeroes == 0) {
    histogram[result].zeroes = zeroes;
  } else if(histogram[result].zeroes != zeroes){
    *double_representation = zeroes;
  }
  return result;
}

void generateKey(struct treeNode *histogram, char *outputFile, int double_representation) {
  int i;
  char *buffer = (char*)malloc(strlen(outputFile) + 4);

  strcpy(buffer, outputFile);
  strcat(buffer, "_key");

  FILE *file;
  file = fopen(buffer, "w");

  if(file == NULL) {
    fprintf(stderr, "Error: Can't open input file - genetateKey()\n");
  }

  fprintf(file, "%d:", double_representation);
  for(i = 0; i < 256; i++) {
    if (histogram[i].freq != 0 || histogram[i].zeroes != 0)
      fprintf(file, "%d:%d:%d:", histogram[i].c, histogram[i].freq, histogram[i].zeroes);
  }
  printf("Your decoding key was saved to: [%s]\n", buffer);

  if(fclose(file))
    fprintf(stderr, "Error: can't close input file - encode()\n");
  free(buffer);
}

void keyToHistogram(char *key_file, struct treeNode *histogram, int *double_representation) {
  int i;
  char buffer;
  char *pch;
  char *key;
  for(i = 0; i < 256; i++) {
    histogram[i].c = i;
    histogram[i].freq = 0;
    histogram[i].zeroes = 0;
  }

  FILE *file;
  file = fopen(key_file, "r");
  if(file == NULL) {
    fprintf(stderr, "Error: Can't open key file - %s\n", key_file);
  }

  fseek(file, 0, SEEK_END);
  key = (char *)malloc(ftell(file) * sizeof(char));
  rewind(file);

  i = 0;
  while(fread(&buffer, 1, 1, file) == 1) {
    key[i++] = buffer;
  }

  pch = strtok(key, ":");
  *double_representation = atoi(pch);
  pch = strtok(NULL, ":");
  while (pch != NULL) {
    i = atoi(pch);
    pch = strtok(NULL, ":");
    histogram[i].freq = atoi(pch);
    pch = strtok(NULL, ":");
    histogram[i].zeroes = atoi(pch);
    pch = strtok(NULL, ":");
  }
  if(fclose(file))
    fprintf(stderr, "Error: can't close key file - %s\n", key_file);
  free(key);
}

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *double_representation) {
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
    if(ftell(iFile) == file_size && *double_representation != -1) {
      histogram[buffer].zeroes = *double_representation;
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

void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram) {
  int i;
  int j = 0;
  int k = histogram[c].zeroes;

  for(i = 7; c != 0; i--) {
    if((c & 1) == 0) {
        buffer[i] = '0';
    }
    else {
      buffer[i] = '1';
    }
      c = c >> 1;
  }
  i++;

  if(i != 0) {
    if(k > 0) {
      for(; k > 0; i--) {
        buffer[i - 1] = '0';
        k--;
      }
    }
    while(buffer[i] != '\0') {
      buffer[j++] = buffer[i++];
    }
    buffer[j] = '\0';
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
