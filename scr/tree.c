#include "tree.h"
#include <stdlib.h>

list *head;

void generateBSTree(bsTree *histogram, int n, bsTree *root) {
  while(n >= 0) {

      bsTree *node = (bsTree *)malloc(sizeof(bsTree));
      node->c = 0;
      node->freq = histogram[n].freq + histogram[n - 1].freq;

    if(root) {
      if(n == 0) {
        node->left = &histogram[n];
        node->right = root;
        root = node;
      } else {
        node->left = &histogram[n - 1];
        node->right = &histogram[n];

        bsTree *new_root = (bsTree *)malloc(sizeof(bsTree));
        new_root->left = node;
        new_root->right = root;
        root = new_root;
      }
    } else {
      node = root;
    }
    n -= 2;
  }
}

void encode(bsTree *root) {
  if(root->c != 0) {
    saveCode(head, root->c);
    delete_list_node(head);
    return;
  }
  insert_list_node(head);
  head->code = 1;
  encode(root->right);
  if(root->left != NULL) {
    //newnode
    head->code = 0;
    encode(root->left);
  }
  delete_list_node(head);
}

list* create_list(void) {
    list *head = (list *)malloc(sizeof(list));
    if (head != NULL) {
        head->code = 2;
        head->next = NULL;
    }
    return head;
}



void saveCode(list *head, char c) {

}

void insert_list_node(list *head) {
  if(head) {
    list *list_node = (list*)malloc(sizeof(list));
    list_node->next = head;
    head = list_node;
  }
  fprintf(stderr, "Empty list, can't add new element\n");
}

void delete_list_node(list *head) {
  list *tmp = head;
  head = head->next;
  head->next = head->next->next;
  free(tmp);
}

void prepare_histogram (bsTree *histogram){
  unsigned int i;
  for(i = 0; i < 256; i++) { //all ASCII codes
    histogram->c = (char)i;
    histogram->freq = 0;
  }
}
