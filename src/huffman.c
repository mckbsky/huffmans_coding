#include "../headers/tree.h"

char **codes;

int main(void) {
    int i;
    struct treeNode histogram[256];

    if(!createHistogram("input.txt", histogram)) {
      return 0;
    }

    quickSort(histogram, 0, 255, 0);

    printf("Number of occurrences of chars in histogram:\n");
     for(i = 0; i < 256; i++) {
             if (histogram[i].freq != 0)
            printf("%c -> %d\n", histogram[i].c, histogram[i].freq);
     }

    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(root == NULL)
      return 0;
    quickSort(histogram, 0, 255, 1);

    struct list_pointers *list = NULL;
    list = (struct list_pointers *)malloc(sizeof(struct list_pointers));
    createList(list);

    codes = (char**)malloc(256 * sizeof(char *));
    for(i = 0; i < 256; i++) {
        codes[i] = NULL;
    }

    createCodes(list, root);
    printf("\nCodes: ");
    for(i = 0; i < 256; i++) {
      if(codes[i] != NULL) {
          printf("\n%c: %s", i, codes[i]);
        }
    }

    encode("input.txt", "encoded.bin", histogram);
    decode(root, "encoded.bin", "decoded.txt", histogram);

    for(i = 0; i < 256; i++) {
        free(codes[i]);
    }
    free(codes);
    removeTree(root);

    return 0;
}
