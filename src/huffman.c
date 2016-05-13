#include <stdlib.h>
#include "../headers/tree.h"


char **codes;

int main(void) {
    struct treeNode histogram[256];
    prepareHistogram(histogram);
    createHistogram("input.txt", histogram);
    int i;

    quickSortFreq(histogram, 0, 255);

    printf("\n");
     for(i = 0; i < 256; i++) {
             if (histogram[i].freq != 0)
            printf("%d -> %d\n", histogram[i].c, histogram[i].freq);
     }
    //print sorted histogram

    // for(i = 0; i < 256; i++) {
    //     if (histogram[i].freq != 0)
    //         printf("%c -> %d\n", histogram[i].c, histogram[i].freq);
    // }

    for(i = 0; i < 256; i++) {
        if(histogram[i].freq == 0)
            break;
    }
    i--;

    struct treeNode *root = NULL;
    root = generateTree(root, histogram, i);

    quickSortChar(histogram, 0, 255);



    struct list_pointers *list = NULL;
    list = (struct list_pointers *)malloc(sizeof(struct list_pointers));
    createList(list);

    codes = (char**)malloc(256 * sizeof(char *));
    createCodes(list, root);

    int j;
    for(i = 0; i < 256; i++) {
        if(codes[i]) {
        printf("\n%c :", i);
            for(j = 0; codes[i][j] != '\0'; j++) {
                printf("%c", codes[i][j]);
            }
        }
    }

    encode("input.txt", "output.txt");
    decode(root, "output.txt", "decoded.txt");
    removeTree(root);

    return 0;
}
