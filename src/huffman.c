#include "../headers/tree.h"

char **codes;

int main(int argc, char **argv) {
  int i;


  //printf("SAP: %d, argv: %s", argc, argv[2]);

  if(argc < 2) {
    printf("ERROR\n"); //TODO: komunikat
  }

  if(argc == 4 && (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-a") == 0)) {
    int double_representation = -1;
    struct treeNode histogram[256];
    printf("SAP: %d, argv[2]: %s, argv[3]: %s\n", argc, argv[2], argv[3]);
    char *buffer;
    if(strcmp(argv[1], "-s") == 0) {
      FILE *file;
      file = fopen("temp.txt", "w");
      while(fprintf(file, "%s", argv[2]) == 1);
      buffer = (char *)malloc(strlen("temp.txt"));
      strcpy(buffer, "temp.txt");
      fclose(file);
    }
    else {
      buffer = (char *)malloc(strlen(argv[2]));
      strcpy(buffer, argv[2]);
    }

    if(!createHistogram(buffer, histogram)) {
      return 0;
    }

    printf("Number of occurrences of chars in histogram:\n");
    for(i = 0; i < 256; i++) {
      if (histogram[i].freq != 0)
        printf("%c -> %d\n", histogram[i].c, histogram[i].freq);
    }

    quickSort(histogram, 0, 255, 0);
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
       printf("\n%d: %s", i, codes[i]);
     }
    }

    printf("\nCompression ratio = %.2lf\n", encode(buffer, argv[3], histogram, &double_representation));

    //generateKey(histogram);

    if(strcmp(argv[1], "-a") == 0) {
      decode(root, argv[3], "decoded.txt", histogram, &double_representation);
    }

    for(i = 0; i < 256; i++) {
      free(codes[i]);
    }

    free(codes);
    free(buffer);
    removeTree(root);
    remove("temp.txt");
  }
  else if(argc == 4 && strcmp(argv[1], "-d") == 0) {
    struct treeNode histogram[256];
    int double_representation = -1;
    //keyToHistogram(argv[3], histogram);
    quickSort(histogram, 0, 255, 0);
    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(root == NULL)
      return 0;
    quickSort(histogram, 0, 255, 1);
    decode(root, argv[3], "decoded.txt", histogram, &double_representation);
  }

  // printf("Number of occurrences of chars in histogram:\n");
  // for(i = 0; i < 256; i++) {
  //   if (histogram[i].freq != 0)
  //     printf("%c -> %d\n", histogram[i].c, histogram[i].freq);
  // }




  //decode(root, "encoded.bin", "decoded.txt", histogram);
  return 0;
}
