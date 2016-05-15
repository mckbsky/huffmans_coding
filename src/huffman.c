#include <stdlib.h>
#include "../headers/tree.h"


char **codes;

int main(void) {
    struct treeNode histogram[256];
    prepareHistogram(histogram);
    if(!createHistogram("input.txt", histogram)) {
      return 0;
    }

    int i;

    quickSortFreq(histogram, 0, 255);

    printf("\n");
     for(i = 0; i < 256; i++) {
             if (histogram[i].freq != 0)
            printf("%d -> %d\n", histogram[i].c, histogram[i].freq);
     }

    for(i = 0; i < 256; i++) {
        if(histogram[i + 1].freq == 0)
            break;
    }

    struct treeNode *root = NULL;
    root = generateTree(root, histogram, i);
    if(root == NULL)
      return 0;
    quickSortChar(histogram, 0, 255);


    struct list_pointers *list = NULL;
    list = (struct list_pointers *)malloc(sizeof(struct list_pointers));
    createList(list);

    codes = (char**)malloc(256 * sizeof(char *));
    createCodes(list, root);
    for(i = 0; i < 256; i++) {
        if(codes[i] != NULL) {
          printf("\n%c: %s", i, codes[i]);
        }
    }

    encode("input.txt", "output.txt");
    decode(root, "output.txt", "decoded.txt");
    removeTree(root);

    return 0;
}
