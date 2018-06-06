#ifndef CODING_H
#define CODING_H

#include "Argument.hpp"
#include "Histogram.hpp"
#include <vector>

#define BYTE_SIZE 8
#define IS_ASCII(c)  (((c) & ~0xFF) == 0)

class Encoder {

private:

    unsigned char binToAscii(unsigned char *binary, Histogram *histogram, int *codeCollision);

public:

    std::vector<char>
    encode(const char *inputFileName, const char *outputFileName, Histogram *histogram, int *codeCollision,
           enum Argument arg,
           char **codes);

    void generateKey(Histogram *histogram, const char *outputFile, int codeCollision);

};


#endif