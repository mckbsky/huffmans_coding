#include "tree.h"
#include <stdlib.h>

list *head;

void generateBSTree(bsTree *histogram, int n, bsTree *root) {
  while(n >= 0) {

      bsTree *node = (bsTree *)malloc(sizeof(bsTree));
      node->c = 0;
      //node->freq = histogram[n].freq + histogram[n - 1].freq;

    if(root) {
     if(n == 0) {
        node->left = (bsTree *)malloc(sizeof(bsTree));
        node->left->c = histogram[n]->c;
        node->right = root;
        root = node;
      } else {
        node->left = (bsTree *)malloc(sizeof(bsTree));
        node->left->c = histogram[n - 1]->c;
        node->right = (bsTree *)malloc(sizeof(bsTree));
        node->right->c = histogram[n]->c;

        bsTree *new_root = (bsTree *)malloc(sizeof(bsTree));
        new_root->c = 0;
        new_root->left = node;
        new_root->right = root;
        root = new_root;
      }
    }
    else if(n == 0){
        node->c = histogram[n]->c;
        root = node;
    }
    else {
        node->left = (bsTree *)malloc(sizeof(bsTree));
        node->left->c = histogram[n - 1]->c;
        node->right = (bsTree *)malloc(sizeof(bsTree));
        node->right->c = histogram[n]->c;
        node = root;
    }
    n -= 2;
  }
}

void encode(bsTree *root) { //TODO: zmienic nazwe na createCodes
  if(root->c != 0) {
    saveCode(head, root->c);
    delete_list_node(head);
    return;
  }
  insert_list_node(head);
  head->code = 1;
  encode(root->right);
  if(root->left != NULL) {
    insert_list_node(head);
    head->code = 0;
    encode(root->left);
  }
  delete_list_node(head);
}

void TMPencode(int (*codes)[256], char *inputFile, char *outputFile) {
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

   while(!feof(iFile)) {
        scanf(iFile,"%c", &buffer);
        fprintf(oFile, "%s", codes[(int)buffer];
   }

    if(fclose(iFile))
    fprintf(stderr, "Error closing input file - function 'encode'\n");
  if(fclose(oFile))
    fprintf(stderr, "Error closing output file - function 'encode'\n");
}

void decode(bsTree *root, char *inputFile, char *outputFile) {
   struct bsTree *tmp = root;
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
    while(1) {
        scanf(file,"%c", &buffer);
        if(buffer = ='0') {
            tmp = tmp->left;
        }
        else if(buffer == '1') {
            tmp = tmp->right;
        }
        if(tmp->c != 0) {
            fprintf(oFile, tmp->c);
            fseek(oFile, 1, SEEK_CURR); //NOTE: moze przesuwac o dwa miejsca, sprawdzic
            tmp = root;
            break;
        }
    fseek(iFile, 1, SEEK_CURR);
    }
  }
  if(fclose(iFile))
    fprintf(stderr, "Error closing input file - function 'decode'\n");
  if(fclose(oFile))
    fprintf(stderr, "Error closing output file - function 'decode'\n");
}

void removeTree(bsTree *root) {
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

list* create_list(void) {
    list *new_node = (list *)malloc(sizeof(list));
    if (new_node != NULL) {
        new_node->code = 2;
        new_node->next = new_node->prev = NULL;
    }
    return new_node;
}

void saveCode(int (*codes)[256], struct list_pointers *top, char c) {
    struct list_node *tmp = tail->prev;
    int i;
    for(i = 0; tmp != NULL; i++) {
        realloc(&codes[(int)c], (i + 1) * sizeof(int));
        codes[(int)c][i] = top->head->code;
        tmp = temp->prev;
    }
}

void insert_list_node(struct list_pointers *top) { //TODO: wyjebac typedefy, zmienic nazwe z top na list
  if(top) {
    list *new_node = (list*)malloc(sizeof(list));
    new_node->prev = NULL;
    new_node->next = top->head;
    top->head->prev = new_node;
    top->head = new_node;
  }
  fprintf(stderr, "Empty list, can't add new element\n");
}

void delete_list_node(struct list_pointers *top) {
    if(top != NULL) {
    list *tmp = top->head->next;
    tmp->prev = NULL;
    free(head);
    head = temp;
    }
    else {
        fprintf(stderr, "Can't delete list node");
    }

}

void prepareHistogram (bsTree *histogram){
  unsigned int i;
  for(i = 0; i < 256; i++) { //all ASCII codes (2^(8 * sizeof(char)))
    histogram->c = (char)i;
    histogram->freq = 0;
  }
}

void create_histogram(char *inputFile, bsTree *histogram) {
  FILE *file;
  char buffer;
  file = fopen(inputFile, "r");
  if(file == NULL) {
    fprintf(stderr, "Error: Can't open input file - function 'create histogram'");
  }
  while(!feof(file)) { //go through file char by char
    fscanf(file,"%c", &buffer);
    histogram[(int)buffer].freq++;
  }
  if(fclose(file))
    fprintf(stderr, "Error closing input file - function 'create histogram'\n");
}


void quickSort(bsTree *histogram, int begin, int end, int flag) {
    //flag = 0 -> po charach
    //flag = 1 -> po frequency
    int i = begin;
    int j = end;
    x = histogram[(i + j) / 2];

    do {
        while(histogram[i] < x) {
            i++;
        }
        while(histogram[j] > x) {
            j++;
        }
        if(i <= j && !flag) {
            char tmp = histogram[i]->c;
            histogram[i]->c = histogram[j]->c;
            histogram[j--]->c = tmp;
            i++;
        }
        else if(i <= j && flag) {
            int tmp = histogram[i]->frequency;
            histogram[i]->frequency = histogram[j]->frequency;
            histogram[j--]->frequency = tmp;
            i++;
        }
    }
    while(i <=j);

    if(begin < j) {
        quickSort(histogram, begin, j, flag);
    }
    if(i < end) {
        quickSort(histogram, i, end, flag);
    }
}
