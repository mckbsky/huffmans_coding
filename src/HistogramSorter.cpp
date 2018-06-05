#include "HistogramSorter.hpp"

void HistrogramSorter::sortCharacters(Histogram *histogram, int begin, int end) {
    int i = begin;
    int j = end;
    int middle;

    middle = histogram->getNode((i + j) / 2).getC();

    do {
        while (histogram->getNode(i).getC() < middle) {
            i++;
        }
        while (histogram->getNode(j).getC() > middle) {
            j--;
        }
        if (i <= j) {
            Node swap = histogram->getNode(i);
            histogram->setNode(i, histogram->getNode(j));
            histogram->setNode(j, swap);

            i++;
            j--;
        }
    } while (i <= j);

    if (begin < j) {
        sortCharacters(histogram, begin, j);
    }
    if (i < end) {
        sortCharacters(histogram, i, end);
    }
}

void HistrogramSorter::sortFrequency(Histogram *histogram, int begin, int end) {
    int i = begin;
    int j = end;
    int middle = histogram->getNode((i + j) / 2).getFreq();

    do {
        while (histogram->getNode(i).getFreq() > middle) {
            i++;
        }
        while (histogram->getNode(j).getFreq() < middle) {
            j--;
        }
        if (i <= j) {
            Node swap = histogram->getNode(i);
            histogram->setNode(i, histogram->getNode(j));
            histogram->setNode(j, swap);

            i++;
            j--;
        }
    } while (i <= j);

    if (begin < j) {
        sortFrequency(histogram, begin, j);
    }
    if (i < end) {
        sortFrequency(histogram, i, end);
    }
}
