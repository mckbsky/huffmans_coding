#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Node.hpp"
#include "Argument.hpp"
#include <cstdio>

class Histogram {

public:

    bool createHistogram(char *inputFile, enum Argument arg);

    Node getNode(int);

    void setNode(int, Node);

    void prepareHistogram();

    long fileSize(FILE *file);

    int findHistogramSize();

private:

    Node histogram[256];

    void fillHistogram(FILE *file);

};

#endif