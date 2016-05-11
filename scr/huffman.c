#include "tree.h"

struct treeNode histogram[256];

int main(void) {
    prepareHistogram(histogram);
    createHistogram("input.txt", histogram);

    //print histogram
    int i;
    for(i = 0; i < 256; i++) {
      if(histogram[i].freq > 0)
        printf("%d -> %d\n", histogram[i].c, histogram[i].freq);
    }

    quickSortChar(histogram, 0, 255);

    return 0;
}
