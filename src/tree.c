#include "../headers/tree.h"
#include <stdlib.h>
#include <string.h>


struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram, int n) {
  while(n >= 0) {
    struct treeNode *node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->c = 0;
    node->freq = histogram[n].freq + histogram[n - 1].freq;

    if(root) {
     if(n == 0) {
        node->left = (struct treeNode *)malloc(sizeof(struct treeNode));
        node->left->freq = histogram[n].freq;
        node->left->c = histogram[n].c;
        node->right = root;
        root = node;
        root->freq = root->left->freq + root->right->freq;
      } else {
        node->left = (struct treeNode *)malloc(sizeof(struct treeNode));
        node->left->freq = histogram[n- 1].freq;
        node->left->c = histogram[n - 1].c;
        node->right = (struct treeNode *)malloc(sizeof(struct treeNode));
        node->right->freq = histogram[n].freq;
        node->right->c = histogram[n].c;
        node->freq = node->left->freq + node->right->freq;

        struct treeNode *new_root = (struct treeNode *)malloc(sizeof(struct treeNode));
        new_root->c = 0;
        new_root->left = node;
        new_root->right = root;
        root = new_root;
        root->freq = root->left->freq + root->right->freq;
      }
    }
    else if(n == 0){
        node->c = histogram[n].c;
        root = node;
        root->freq = histogram[n].freq;
    }
    else {
        node->left = (struct treeNode *)malloc(sizeof(struct treeNode));
        node->left->c = histogram[n - 1].c;
        node->right = (struct treeNode *)malloc(sizeof(struct treeNode));
        node->right->c = histogram[n].c;
        root = node;
    }
    n -= 2;
  }
  printf("Weight of tree: %d", root->freq);
  return root;
}

void createCodes(struct list_pointers *list, struct treeNode *root) {
  if(root->c != 0 && list->head == list->tail) {
    insertListNode(list);
    list->head->code = '0';
    saveCode(list, root->c);
    deleteListNode(list);
    return;
  }

  if(root->c != 0) {
    saveCode(list, root->c);
    deleteListNode(list);
    return;
  }

  insertListNode(list);
  list->head->code = '1';
  createCodes(list, root->right);
    insertListNode(list);
    list->head->code = '0';
    createCodes(list, root->left);
    deleteListNode(list);

}

void saveCode(struct list_pointers *list, char c) {
    struct list_node *tmp = list->tail->prev;
    int unsigned i;
    for(i = 0; tmp != NULL; i++) {
        codes[(int)c] = (char *)realloc(codes[(int)c], (i + 2) * sizeof(char));
        codes[(int)c][i] = tmp->code;
        codes[(int)c][i + 1] = '\0';
        tmp = tmp->prev;
    }
}

void encode(char *inputFile, char *outputFile) {
    FILE *iFile, *oFile;
   char buffer;
  iFile = fopen(inputFile, "r");
  oFile = fopen(outputFile, "w");
  if(iFile == NULL) {
    fprintf(stderr, "Error: Can't open input file - function 'encode'");
  }
 if(oFile == NULL) {
    fprintf(stderr, "Error: Can't open output file - function 'encode'");
  }

   while(fscanf(iFile,"%c", &buffer) == 1) {
        fprintf(oFile, "%s", codes[(int)buffer]);
   }

    if(fclose(iFile))
    fprintf(stderr, "Error closing input file - function 'encode'\n");
  if(fclose(oFile))
    fprintf(stderr, "Error closing output file - function 'encode'\n");
}

void decode(struct treeNode *root, char *inputFile, char *outputFile) {
  struct treeNode *tmp = root;
  FILE *iFile, *oFile;
  char buffer;
  iFile = fopen(inputFile, "r");
  oFile = fopen(outputFile, "w");
  if(iFile == NULL) {
    fprintf(stderr, "Error: Can't open input file - function 'decode'");
  }
  if(oFile == NULL) {
    fprintf(stderr, "Error: Can't open output file - function 'decode'");
  }
  while(!feof(iFile)) {
    fscanf(iFile, "%c", &buffer);
    if(tmp->c != 0) {
      fprintf(oFile, "%c", tmp->c);
      tmp = root;
    }
    if(buffer == '0') {
      tmp = tmp->left;
    }
    else if(buffer == '1') {
      tmp = tmp->right;
    }
  }
  if(fclose(iFile))
    fprintf(stderr, "Error closing input file - function 'decode'\n");
  if(fclose(oFile))
    fprintf(stderr, "Error closing output file - function 'decode'\n");
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
    fprintf(stderr, "Empty list, can't add new element\n");
  }
}

void deleteListNode(struct list_pointers *list) {
    if(list->head == list->tail) {
        free(list->head);
        list = NULL;
    }
    else if(list->head) {
        struct list_node *tmp = list->head->next;
        tmp->prev = NULL;
        free(list->head);
        list->head = tmp;
    }
    else {
        fprintf(stderr, "Can't delete list node");
    }
}

void prepareHistogram (struct treeNode *histogram) {
  unsigned int i;
  for(i = 0; i < 256; i++) { //all ASCII codes (2^(8 * sizeof(char)))
    histogram[i].c = (char)i;
    histogram[i].freq = 0;
  }
}

bool createHistogram(char *inputFile, struct treeNode *histogram) {
  FILE *file;
  char buffer;
  file = fopen(inputFile, "r");
  if(file == NULL) {
    fprintf(stderr, "Error: Can't open input file - function 'create histogram'\n");
    return false;
  }
  fseek(file, 0, SEEK_END);
  if(ftell(file) == 0) {
    fprintf(stderr, "Error: empty input file\n");
    return false;
  } else {
    rewind(file);
  }
  while(fscanf(file, "%c", &buffer) == 1) { //go through file char by char
    histogram[(int)buffer].freq++; //FIXME: dodaje o jeden znak za duzo
  }
  if(fclose(file)) {
    fprintf(stderr, "Error closing input file - function 'create histogram'\n");
    return false;
  }
  return true;
}

void quickSortChar(struct treeNode *histogram, int begin, int end) {
    int i = begin;
    int j = end;
    int x;

    x = histogram[(i + j) / 2].c;

    do {
        while(histogram[i].c < x) {
            i++;
        }
        while(histogram[j].c > x) {
            j--;
        }
        if(i <= j) {
            char tmp = histogram[i].c;
            histogram[i].c = histogram[j].c;
            histogram[j].c = tmp;

            int tmp2 = histogram[i].freq;
            histogram[i].freq = histogram[j].freq;
            histogram[j].freq = tmp2;
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
    int x = histogram[(i + j) / 2].freq;

    do {
        while(histogram[i].freq > x) {
            i++;
        }
        while(histogram[j].freq < x) {
            j--;
        }
        if(i <= j) {
            int tmp = histogram[i].freq;
            histogram[i].freq = histogram[j].freq;
            histogram[j].freq = tmp;

            char tmp2 = histogram[i].c;
            histogram[i].c = histogram[j].c;
            histogram[j].c = tmp2;
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
