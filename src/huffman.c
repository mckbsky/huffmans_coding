#include <stdlib.h>
#include "../headers/tree.h"

struct treeNode histogram[256];
int **codes;

int main(void) {
    prepareHistogram(histogram);
    createHistogram("input.txt", histogram);

    quickSortFreq(histogram, 0, 255);

    //print sorted histogram
    int i;
    for(i = 0; i < 256; i++) {
        if (histogram[i].freq != 0)
            printf("%c -> %d\n", histogram[i].c, histogram[i].freq);
    }

    for(i = 0; i < 256; i++) {
        if(histogram[i].freq == 0)
            break;
    }
    i--;

    struct treeNode *root = NULL;
    root = generateTree(root, i);

    quickSortChar(histogram, 0, 255);

    for(i = 0; i < 256; i++) {
            if (histogram[i].freq != 0)
            printf("%d -> %d\n", histogram[i].c, histogram[i].freq);
    }

    struct list_pointers *list = NULL;
    list = (struct list_pointers *)malloc(sizeof(struct list_pointers));
    createList(list);

    createCodes(list, root);

    removeTree(root);

    return 0;
}
