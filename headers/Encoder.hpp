#ifndef CODING_H
#define CODING_H

#include "Argument.hpp"
#include "Histogram.hpp"

#define BYTE_SIZE 8
#define IS_ASCII(c)  (((c) & ~0xFF) == 0)

class Encoder {

private:

    unsigned char binToAscii(unsigned char *binary, Histogram *histogram, int *codeCollision);

public:

    double
    encode(char *inputFileName, char *outputFileName, Histogram *histogram, int *codeCollision, enum Argument arg,
           char **codes);

    void generateKey(Histogram *histogram, char *outputFile, int codeCollision);

};


#endif