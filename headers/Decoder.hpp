#ifndef DECODER_HPP
#define DECODER_HPP

#include "Histogram.hpp"

#define BYTE_SIZE 8

class Decoder {

public:
    void keyToHistogram(char *keyFileName, Histogram *histogram, int *codeCollision);

    void
    decode(Node *root, char *inputFileName, const char *outputFileName, Histogram *histogram, const int *codeCollision);

    void asciiToBin(unsigned char ascii, unsigned char *binary, Histogram *histogram);

};

#endif
