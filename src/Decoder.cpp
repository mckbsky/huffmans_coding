#include <Decoder.hpp>
#include <cstdlib>
#include <cstring>
#include <cstdio>

void Decoder::keyToHistogram(char *keyFileName, Histogram *histogram, int *codeCollision) {
    char *token;
    char *key;

    histogram->prepareHistogram();

    FILE *file = fopen(keyFileName, "r");
    if (file == nullptr) {
        fprintf(stderr, "Error: Can't open key file - %s\n", keyFileName);
        return;
    }

    long keyFileSize = histogram->fileSize(file);
    key = (char *) malloc(static_cast<size_t>(keyFileSize));

    int i = 0;
    char buffer;
    while (fread(&buffer, 1, 1, file) == 1) {
        key[i++] = buffer;
    }

    const char *delimeter = ":";

    token = strtok(key, delimeter);
    *codeCollision = atoi(token);
    token = strtok(nullptr, delimeter);
    while (token != nullptr) {
        i = atoi(token);
        token = strtok(nullptr, delimeter);
        histogram->getNode(i).setFreq(atoi(token));
        token = strtok(nullptr, delimeter);
        histogram->getNode(i).setZeroes(atoi(token));
        token = strtok(nullptr, delimeter);
    }

    if (fclose(file)) {
        fprintf(stderr, "Error: can't close key file - %s\n", keyFileName);
    }

    free(key);
}

void Decoder::decode(Node *root, char *inputFileName, const char *outputFileName, Histogram *histogram,
                     const int *codeCollision) {
    Node *tmp = root;
    FILE *inputFile, *outputFile;

    inputFile = fopen(inputFileName, "rb");
    outputFile = fopen(outputFileName, "w");

    if (inputFile == nullptr) {
        fprintf(stderr, "Error: Can't open input file - %s\n", inputFileName);
    }
    if (outputFile == nullptr) {
        fprintf(stderr, "Error: Can't open output file - %s\n", outputFileName);
    }

    long inputFileSize;
    inputFileSize = histogram->fileSize(inputFile);

    unsigned char parsedChar;
    unsigned char binary[BYTE_SIZE + 1] = {0};
    while (fread(&parsedChar, 1, 1, inputFile) == 1) {
        if (ftell(inputFile) == inputFileSize && *codeCollision != -1) {
            histogram->getNode(parsedChar).setZeroes(*codeCollision);
        }
        asciiToBin(parsedChar, binary, histogram);

        for (int i = 0; binary[i] != '\0'; ++i) {
            if (binary[i] == '0' && tmp->getLeft() != nullptr) {
                tmp = tmp->getLeft();
            } else if (binary[i] == '1' && tmp->getRight() != nullptr) {
                tmp = tmp->getRight();
            }
            if (tmp->getLeft() == nullptr && tmp->getRight() == nullptr) {
                fprintf(outputFile, "%c", tmp->getC());
                tmp = root;
            }
        }
        memset(binary, 0, sizeof(binary));
    }

    if (fclose(inputFile))
        fprintf(stderr, "Error: Can't close input file - %s\n", outputFileName);
    if (fclose(outputFile))
        fprintf(stderr, "Error: Can't close output file - %s\n", outputFileName);

    printf("Decoding of file [%s] successful!\n", inputFileName);
}

void Decoder::asciiToBin(unsigned char ascii, unsigned char *binary, Histogram *histogram) {
    int i;
    int j = 0;
    int zeroes = histogram->getNode(ascii).getZeroes();

    for (i = BYTE_SIZE - 1; ascii != 0; --i) {
        binary[i] = (ascii & 1) == 0 ? '0' : '1';
        ascii >>= 1;
    }
    i += 1;

    if (i != 0) {
        if (zeroes > 0) {
            for (; zeroes > 0; --zeroes) {
                binary[(i--) - 1] = '0';
            }
        }

        while (binary[i] != '\0') {
            binary[j++] = binary[i++];
        }
        binary[j] = '\0';
    }
}
