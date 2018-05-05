#include <iostream>
#include <cstring>
#include "Histogram.hpp"

bool Histogram::createHistogram(char *inputFile, enum Argument arg) {
    FILE *file = nullptr;

    if (arg == ENCODE || arg == ALL) {
        file = fopen(inputFile, "r");
    } else if (arg == STRING) {
        file = fmemopen((void *) inputFile, strlen(inputFile), "r");
    } else {
        return false;
    }

    if (nullptr == file) {
        std::cerr << "Error: Can't open input file - createHistogram()" << std::endl;
        return false;
    }

    if (fileSize(file) == 0) {
        std::cerr << "Error: empty input file" << std::endl;
        return false;
    }

    this->histogram = new Node[256];
    prepareHistogram();
    fillHistogram(file);

    if (fclose(file)) {
        std::cerr << "Error: Can't close input file - createHistogram()" << std::endl;
        return false;
    }

    return true;
}

void Histogram::prepareHistogram() {
    int i;
    for (i = 0; i < 256; i++) {
        histogram[i].setC(static_cast<unsigned char>(i));
        histogram[i].setFreq(0);
        histogram[i].setZeroes(0);
    }
}

void Histogram::fillHistogram(FILE *file) {
    char character;
    while (fscanf(file, "%c", &character) == 1) {
        histogram[(int) character].setFreq(histogram->getFreq() + 1);
    }
}

int Histogram::findHistogramSize() {
    for (int size = 0; size < 256; ++size) {
        if (histogram[size + 1].getFreq() == 0)
            return size;
    }
    return 0;
}

long Histogram::fileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    return size;
}

Node *Histogram::getNode(int n) {
    return &this->histogram[n];
}

void Histogram::setNode(int n, Node *node) {
    this->histogram[n] = *node;
}


