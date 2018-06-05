#include <cstdio>
#include <Encoder.hpp>
#include <cerrno>
#include <iostream>
#include <cmath>
#include <cstring>

std::vector<char> Encoder::encode(char *inputFileName, char *outputFileName, Histogram *histogram, int *codeCollision,
                                  enum Argument arg, char **codes) {
    FILE *inputFile = nullptr;
    FILE *outputFile = fopen(outputFileName, "wb");
    long inputFileSize = 0, outputFileSize = 0;
    std::vector<char> out;

    if (arg == ENCODE || arg == ALL) {
        inputFile = fopen(inputFileName, "r");
    } else if (arg == STRING) {
        inputFile = fmemopen((void *) inputFileName, strlen(inputFileName), "r");
    } else {
        std::cerr << "Error";
        return {};
    }

    if (inputFile == nullptr) {
        std::cerr << "Error: Can't open input file - " << inputFileName << std::endl;
        return {};
    }
    if (outputFile == nullptr) {
        std::cerr << "Error: Can't open output file - " << outputFileName << std::endl;
        return {};
    }

    int i = 1;
    int j = 0;

    unsigned char parsedChar;
    unsigned char byte[BYTE_SIZE + 1] = {0};

    while (fscanf(inputFile, "%c", &parsedChar) == 1) {
        if (!IS_ASCII(parsedChar)) {
            std::cerr << "Found non-ASCII character ->  " << parsedChar << +", exiting..." << std::endl;
            return {};
        }
        inputFileSize++;
        while (true) {

            if (codes[parsedChar][j] != '\0') {
                byte[i - 1] = static_cast<unsigned char>(codes[parsedChar][j]);
                i++;
                j++;
            } else {
                if (fscanf(inputFile, "%c", &parsedChar) == 1) {
                    inputFileSize++;
                    j = 0;
                } else {
                    break;
                }
            }
            if (i > BYTE_SIZE) {
                unsigned char tmp = binToAscii(byte, histogram, codeCollision);
                fwrite(&tmp, 1, 1, outputFile);
                out.emplace_back(tmp);
                outputFileSize++;
                memset(byte, 0, sizeof(byte));
                i = 1;
            }
        }
        if (i < BYTE_SIZE) {
            unsigned char tmp = binToAscii(byte, histogram, codeCollision);
            fwrite(&tmp, 1, 1, outputFile);
            out.emplace_back(tmp);
            outputFileSize++;
        }
    }

    if (fclose(inputFile)) {
        std::cerr << "Error: can't close input file - encode()" << std::endl;
    }
    if (fclose(outputFile)) {
        std::cerr << "Error: can't close output file - encode()" << std::endl;
    }

    std::cout << "Encoding of [" << inputFileName << "] successful!" << std::endl;
    return out;
}

unsigned char Encoder::binToAscii(unsigned char *binary, Histogram *histogram, int *codeCollision) {
    int i, j;
    int zeroes = 0;
    unsigned char ascii = 0;

    for (i = 0; binary[i + 1] != '\0'; ++i);

    for (j = 0; i >= 0; --i) {
        if (binary[i] == '1') {
            ascii += pow(2, j);
        }
        j += 1;
    }

    for (j = 0; binary[j] == '0'; ++j) {
        zeroes += 1;
    }

    if (zeroes != 0 && histogram->getNode(ascii).getZeroes() == 0) {
        histogram->getNode(ascii).setZeroes(zeroes);
    } else if (histogram->getNode(ascii).getZeroes() != zeroes) {
        *codeCollision = zeroes;
    }
    return ascii;
}


void Encoder::generateKey(Histogram *histogram, char *outputFile, int codeCollision) {
    auto postfix = "_key";
    auto keyFileName = (char *) malloc(strlen(outputFile) + strlen(postfix));

    strcpy(keyFileName, outputFile);
    strcat(keyFileName, postfix);

    auto file = fopen(keyFileName, "w");

    if (file == nullptr) {
        fprintf(stderr, "Error: Can't open input file - %s\n", keyFileName);
        return;
    }

    fprintf(file, "%d:", codeCollision);
    for (int i = 0; i < 256; ++i) {
        if (histogram->getNode(i).getFreq() != 0 || histogram->getNode(i).getZeroes() != 0)
            fprintf(file, "%d:%d:%d:", histogram->getNode(i).getC(), histogram->getNode(i).getFreq(),
                    histogram->getNode(i).getZeroes());
    }
    std::cout << "Your decoding key was saved to: [" << keyFileName << "]" << std::endl;

    if (fclose(file)) {
        std::cout << "Error: can't close input file - encode()" << std::endl;
    }

    free(keyFileName);
}
