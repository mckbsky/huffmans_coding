#include "../headers/tree.h"
#include <time.h>

char **codes;

void printHelp() {
    printf("Huffman's Coding\n");
    printf("Available Commands:\n");
    printf("-e [input] [output] - encodes your input file and saves it to output file\n");
    printf("-s [string] [output] - encodes your string and saves it to output file\n");
    printf("-d [input] [output] [key] - decodes your input file and saves it to output file. It uses key generated with either '-s' or '-e'\n");
    printf("-a [input] [output] - perform encoding and decoding -- used for debugging purposes\n");
    printf("-authors - prints authors of this application\n");
}

enum argument {
  ENCODE, DECODE, STRING, ALL, AUTHORS
};

enum argument checkArgument(char **argv) {
  if(strcmp(argv[1], "-e") == 0) {
    return ENCODE;
  }
  else if(strcmp(argv[1], "-d") == 0) {
    return DECODE;
  }
  else if(strcmp(argv[1], "-s") == 0) {
    return STRING;
  }
  else if(strcmp(argv[1], "-a") == 0) {
    return ALL;
  }
  else if(strcmp(argv[1], "-authors") == 0) {
    return AUTHORS;
  }
}

int main(int argc, char **argv) {
  if(argc < 2) {
    printHelp();
    return 0;
  }

  if(argc == 4 && (checkArgument(argv) == ENCODE || checkArgument(argv) == STRING || checkArgument(argv) == ALL)) {
    int i;
    int double_representation = -1;
    struct treeNode histogram[256];
    char *buffer;
    clock_t startt, resultt;

    if(checkArgument(argv) == STRING) {

      startt = clock();

      FILE *file;
      file = fopen("temp.txt", "w");
      while(fprintf(file, "%s", argv[2]) == 1);
      buffer = (char *)malloc(strlen("temp.txt"));
      strcpy(buffer, "temp.txt");
      fclose(file);
    } else {

      startt = clock();

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

    printf("Compression ratio = %.2lf\n", encode(buffer, argv[3], histogram, &double_representation));

    generateKey(histogram, argv[3], double_representation);

    if(strcmp(argv[1], "-a") == 0) {
      resultt = clock() - startt;
      printf("Algorithm for -a before decoding took %f seconds.\n",((float)resultt)/CLOCKS_PER_SEC);
      decode(root, argv[3], "decoded.txt", histogram, &double_representation);
    }

    for(i = 0; i < 256; i++) {
      free(codes[i]);
    }

    free(codes);
    free(buffer);
    removeTree(root);
    remove("temp.txt");
    resultt = clock() - startt;
    printf("Algorithm for your text took %f seconds.\n",((float)resultt)/CLOCKS_PER_SEC);

  } else if(argc == 5 && checkArgument(argv) == DECODE) {

    clock_t startt, resultt;
    startt = clock();

    struct treeNode histogram[256];
    int double_representation = -1;

    keyToHistogram(argv[4], histogram, &double_representation);
    quickSortFreq(histogram, 0, 255);
    struct treeNode *root = NULL;
    root = generateTree(root, histogram);
    if(root == NULL)
      return 0;
    quickSortChar(histogram, 0, 255);

    decode(root, argv[2], argv[3], histogram, &double_representation);
    removeTree(root);
    resultt = clock() - startt;
    printf("Algorithm for decoding your text took %f seconds.\n",((float)resultt)/CLOCKS_PER_SEC);
  } else if(argc == 2 && checkArgument(argv) == AUTHORS) {
    printf("Authors:\n");
    printf("Maciej Brzeczkowski <maciej.brzeczkowski@protonmail.com>\n");
    printf("Mariusz Lewczuk\n");
  } else {
    printf("Incorrect arguments");
  }

  return 0;
}
