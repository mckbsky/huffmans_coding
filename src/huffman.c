#include "../headers/tree.h"

char **codes;

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Huffman's Coding\n");
    printf("Available Commands:\n");
    printf("-e [input] [output] - encodes your input file and saves it to output file\n");
    printf("-s [string] [output] - encodes your string and saves it to output file\n");
    printf("-d [input] [output] [key] - decodes your input file and saves it to output file. It uses key generated with either '-s' or '-e'\n");
    printf("-a [input] [output] - perform encoding and decoding -- used for debugging purposes\n");
    printf("-authors - prints authors of this application\n");
  }

  if(argc == 4 && (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-a") == 0)) {
    int i;
    int double_representation = -1;
    struct treeNode histogram[256];
    char *buffer;

    if(strcmp(argv[1], "-s") == 0) {
      FILE *file;
      file = fopen("temp.txt", "w");
      while(fprintf(file, "%s", argv[2]) == 1);
      buffer = (char *)malloc(strlen("temp.txt"));
      strcpy(buffer, "temp.txt");
      fclose(file);
    } else {
      buffer = (char *)malloc(strlen(argv[2]));
      strcpy(buffer, argv[2]);
    }

    if(!createHistogram(buffer, histogram)) {
      return 0;
    }

    quickSortFreq(histogram, 0, 255);
    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(root == NULL)
      return 0;

    quickSortChar(histogram, 0, 255);

    struct list_pointers *list = NULL;
    list = (struct list_pointers *)malloc(sizeof(struct list_pointers));
    createList(list);

    codes = (char**)malloc(256 * sizeof(char *));
    for(i = 0; i < 256; i++) {
      codes[i] = NULL;
    }
    createCodes(list, root);

    /*printf("\nCodes: ");
    for(i = 0; i < 256; i++) {
     if(codes[i] != NULL) {
       printf("\n%d: %s", i, codes[i]);
     }
    }*/

    printf("Compression ratio = %.2lf\n", encode(buffer, argv[3], histogram, &double_representation));

    generateKey(histogram, double_representation);

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

    printf("Process completed after seconds\n");
  }
  else if(argc == 4 && strcmp(argv[1], "-d") == 0) { //decoding
    struct treeNode histogram[256];
    int double_representation = -1;

    keyToHistogram(argv[3], histogram, &double_representation);
    quickSortFreq(histogram, 0, 255);
    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(root == NULL)
      return 0;
    quickSortChar(histogram, 0, 255);

    decode(root, argv[2], "decoded.txt", histogram, &double_representation);

    printf("Process completed after seconds\n");
  }

  return 0;
}
