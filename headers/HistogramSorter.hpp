#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Histogram.hpp"

class HistrogramSorter {

public:

    void sortCharacters(Histogram *histogram, int begin, int end);

    void sortFrequency(Histogram *histogram, int begin, int end);

};


#endif