#include "../headers/tree.h"

bool createHistogram(char *inputFile, struct treeNode *histogram) {
  FILE *file;
  char buffer;
  file = fopen(inputFile, "r");

  if(file == NULL) {
    fprintf(stderr, "Error: Can't open input file - createHistogram()\n");
    return false;
  }

  fseek(file, 0, SEEK_END);
  if(ftell(file) == 0) {
    fprintf(stderr, "Error: empty input file\n");
    return false;
  } else {
    rewind(file);
  }

  int i;
  for(i = 0; i < 256; i++) {
    histogram[i].c = (char)i;
    histogram[i].freq = 0;
    histogram[i].zeroes = 0;
  }

  while(fscanf(file, "%c", &buffer) == 1) {
    histogram[(int)buffer].freq++;
  }

  if(fclose(file)) {
    fprintf(stderr, "Error: Can't close input file - createHistogram()\n");
    return false;
  }
  return true;
}

void quickSort(struct treeNode *histogram, int begin, int end, int type) {
  int i = begin;
  int j = end;
  int x = *getHistogram(histogram, (i + j) / 2, type);

  do {
      while(*getHistogram(histogram, i, type) > x) {
          i++;
      }
      while(*getHistogram(histogram, j, type) < x) {
          j--;
      }
      if(i <= j) {
        int tmp = *getHistogram(histogram, i, type);
         *getHistogram(histogram, i, type) = *getHistogram(histogram, j, type);
         *getHistogram(histogram, j, type) = tmp;

        tmp = *getHistogram(histogram, i, !type);
        *getHistogram(histogram, i, !type) = *getHistogram(histogram, j, !type);
        *getHistogram(histogram, j, !type) = tmp;

        //tmp = histogram[i].zeroes;
        //histogram[i].zeroes = histogram[j].zeroes;
        //histogram[j].zeroes = tmp;

        i++; j--;
      }
  }
  while(i <= j);

  if(begin < j) {
    quickSort(histogram, begin, j, type);
  }
  if(i < end) {
    quickSort(histogram, i, end, type);
  }
}

int *getHistogram(struct treeNode *histogram, int i, int type) {
  if(type == 0) {
    return &histogram[i].freq;
  }
  else if(type == 1) {
    return &histogram[i].c;
  }
  else {
    fprintf(stderr, "Error: wrong quickSort type\n");
    return NULL;
  }
}

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram) {
  int n;
  for(n= 0; n < 256; n++) {
    if(histogram[n + 1].freq == 0)
       break;
  }

  while(n >= 0) {
    struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));

    if(root) {
    if(n == 0) {
        node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
        node->left->c = histogram[n].c;
        node->right = root;
        root = node;
      } else {
        node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
        node->left->c = histogram[n - 1].c;
        node->right = (struct treeNode *)calloc(1, sizeof(struct treeNode));
        node->right->c = histogram[n].c;

        struct treeNode *new_root = (struct treeNode *)calloc(1, sizeof(struct treeNode));
        new_root->left = node;
        new_root->right = root;
        root = new_root;
      }
    }
    else if(n == 0){
      node->c = histogram[n].c;
      root = node;
    }
    else {
      node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
      node->left->c = histogram[n - 1].c;
      node->right = (struct treeNode *)calloc(1, sizeof(struct treeNode));
      node->right->c = histogram[n].c;
      root = node;
    }
    n -= 2;
  }
  return root;
}

void createCodes(struct list_pointers *list, struct treeNode *root) {
  if(root->c != 0 && list->head == list->tail) {
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

void saveCode(struct list_pointers *list, char c) {
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
    if(*double_representation != -1) {
      printf("\n%d zeroes at the end", *double_representation);
    }
    fwrite(&tmp, 1, 1, oFile);
    oFileSize++;
  }

  if(fclose(iFile))
    fprintf(stderr, "Error: can't close input file - encode()\n");
  if(fclose(oFile))
    fprintf(stderr, "Error: can't close output file - encode()\n");

    return (double)oFileSize / iFileSize;
}

unsigned char binToAscii(unsigned char *array, struct treeNode *histogram, int *double_representation) {
  int i;
  int j;
  int zeroes = 0;
  unsigned char result = 0;

  for(i = 0; array[i + 1] != '\0'; i++);

  for(j = 0; i >= 0; i--) {
    if(array[i] == '1') {
      result += pow(2, j++);
    }
    else {
      j++;
    }
  }
  for(j = 0; array[j] == '0'; j++) {
    zeroes++;
  }
  if(zeroes != 0 && histogram[result].zeroes == 0) {
    histogram[result].zeroes = zeroes;
    printf("\n%d -> %d zeroes", result, histogram[result].zeroes);
  } else if(histogram[result].zeroes != zeroes){
    printf("\nDouble representation of binary");
    printf("\n%d -> %d zeroes", result, zeroes);
    *double_representation = zeroes;
  }
  //if(histogram[result].zeroes == 0) {
  //  for(j = 0; array[j] == '0'; j++) {
  //    histogram[result].zeroes++;
  //  }
  //}

  return result;
}

void generateKey(struct treeNode *histogram) {
  int i;
  for(i = 0; i < 256; i++) {
    if (histogram[i].freq != 0)
      printf("%d:%d:%d:", histogram[i].c, histogram[i].freq, histogram[i].zeroes);
  }
}

void keyToHistogram(char *key, struct treeNode *histogram) {
  int i;
  for(i = 0; i < 256; i++) {
    histogram[i].c = (char)i;
    histogram[i].freq = 0;
    histogram[i].zeroes = 0;
  }

}

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *double_representation) {
  struct treeNode *tmp = root;
  FILE *iFile, *oFile;
  unsigned char buffer;
  unsigned char buffer_arr[9];
  int i;
  int j = 0;
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
  printf("\nFILE SIZE: %d", file_size);
  printf("\nFILE BEGIN: %lu\n", ftell(iFile));

  while(fread(&buffer, 1, 1, iFile) == 1) {
    j++;
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
  printf("\nBUFFER: %d", buffer);
  printf("\nJ: %d", j);
  if(fclose(iFile))
    fprintf(stderr, "Error: Can't close input file - decode()\n");
  if(fclose(oFile))
    fprintf(stderr, "Error: Can't close output file - decode()\n");
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
  if(root->c != 0) {
    free(root);
    return;
  }
  removeTree(root->right);
  if(root->left != NULL) {
    removeTree(root->left);
  }
  free(root);
}
