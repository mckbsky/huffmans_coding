#include "Huffman.hpp"
#include <HistogramSorter.hpp>

#include <cerrno>
#include <iostream>
#include <Encoder.hpp>
#include <Decoder.hpp>
#include <cstring>

int main(int argc, char **argv) {
    auto *huffman = new Huffman();
    auto arg = huffman->checkArgument(argc, argv);
    clock_t startTime, resultTime;
    startTime = clock();

    if (arg == HELP) {
        huffman->printHelp();
        return EXIT_SUCCESS;
    } else if (arg == ENCODE || arg == STRING || arg == ALL) {
        double encodeTime = huffman->doEncode(argv, arg);
        printf("Compression ratio = %.2lf\n", encodeTime);
    } else if (arg == DECODE) {
        huffman->doDecode(argv[2], argv[3], argv[4]);
    } else if (arg == AUTHORS) {
        huffman->printAuthors();
        return EXIT_SUCCESS;
    } else if (arg == INVALID) {
        fprintf(stderr, "Incorrect arguments\n");
        return -EINVAL;
    }

    resultTime = clock() - startTime;
    printf("Algorithm took %f seconds.\n", ((float) resultTime) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}


enum Argument Huffman::checkArgument(int argc, char **argv) {
    if (argc < 2) {
        return HELP;
    } else if (argc == 4) {
        if (strcmp(argv[1], "-e") == 0) {
            return ENCODE;
        } else if (strcmp(argv[1], "-s") == 0) {
            return STRING;
        } else if (strcmp(argv[1], "-a") == 0) {
            return ALL;
        }
    } else if (argc == 5) {
        if (strcmp(argv[1], "-d") == 0) {
            return DECODE;
        }
    } else if (strcmp(argv[1], "--authors") == 0) {
        return AUTHORS;
    }
    return INVALID;
}

void Huffman::printHelp() {
    printf("Huffman's Coding\n");
    printf("Available Commands:\n");
    printf("-e [input] [output] - encodes your input file and saves it to output file\n");
    printf("-s [string] [output] - encodes your string and saves it to output file\n");
    printf("-d [input] [output] [key] - decodes your input file and saves it to output file. It uses key generated with either '-s' or '-e'\n");
    printf("-a [input] [output] - perform encoding and decoding -- used for debugging purposes\n");
    printf("--authors - prints authors of this application\n");
}

double Huffman::doEncode(char **argv, Argument arg) {
    int codeCollision = -1;
    Node *root = nullptr;
    auto *histogram = new Histogram();
    double encodeTime;

    if (!histogram->createHistogram(argv[2], arg)) {
        fprintf(stderr, "Error creating histogram\n");
        return -1.0;
    }

    HistrogramSorter sorter;
    sorter.sortFrequency(histogram, 0, ASCII_TABLE_SIZE - 1);
    auto *tree = new Tree();
    root = tree->generateTree(root, histogram);
    if (nullptr == root) {
        std::cerr << "Error generating tree" << std::endl;
    }

    sorter.sortCharacters(histogram, 0, ASCII_TABLE_SIZE - 1);
    createCodeTable(tree);

    Encoder encoder;
    encodeTime = encoder.encode(argv[2], argv[3], histogram, &codeCollision, arg, codes);
    encoder.generateKey(histogram, argv[3], codeCollision);

    if (arg == ALL) {
        Decoder decoder;
        decoder.decode(root, argv[3], "decoded.txt", histogram, &codeCollision);
    }

    freeMemory(tree);
    return encodeTime;
}

void Huffman::printAuthors() {
    printf("Authors:\n");
    printf("Maciej Brzeczkowski <maciej.brzeczkowski@protonmail.com>\n");
}

void Huffman::doDecode(char *input, char *output, char *key) {
    auto histogram = new Histogram();
    int codeCollision = -1;

    Decoder decoder;
    decoder.keyToHistogram(key, histogram, &codeCollision);
    HistrogramSorter sorter;
    sorter.sortFrequency(histogram, 0, ASCII_TABLE_SIZE - 1);

    Node *root = nullptr;
    auto *tree = new Tree();
    root = tree->generateTree(root, histogram);
    if (nullptr == root) {
        std::cerr << "Error creating tree" << std::endl;
        return;
    }

    sorter.sortCharacters(histogram, 0, ASCII_TABLE_SIZE - 1);

    decoder.decode(root, input, output, histogram, &codeCollision);
    tree->removeTree(root);
}

void Huffman::freeMemory(Tree *tree) {
    int i;
    for (i = 0; i < ASCII_TABLE_SIZE; i++) {
        free(codes[i]);
    }
    free(codes);
    tree->removeTree(tree->getRoot());
}

void Huffman::createCodeTable(Tree *tree) {
    auto *list = new List();
    list->createList();

    codes = (char **) malloc(ASCII_TABLE_SIZE * sizeof(char *));
    for (int i = 0; i < ASCII_TABLE_SIZE; i++) {
        codes[i] = nullptr;
    }
    tree->createCodes(tree->getRoot(), list);
}

int Huffman::ASCII_TABLE_SIZE = 256;
