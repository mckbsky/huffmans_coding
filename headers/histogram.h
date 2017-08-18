#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <stdio.h>
#include <string.h>
#include "../headers/tree.h"
#include "../headers/argument.h"

extern struct treeNode* histogram;

/*!
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram)
 * \brief Funkcja tworząca histogram
 *
 * \param char *inputFile - nazwa pliku wejściowego,
 * \param struct treeNode *histogram  - tablica typu strukturalnego z informacjami
 * o danym znaku, ilości jego wystąpień i liczbie zer do wypełnienia dla kodu.
 * \return Wartość bool zależną od powodzenia działania funkcji.
 *
 * Funkcja generuje histogram zliczając ilość wystąpień danego znaku w
 * pliku wejściowym i zapisuje tą informację do tablicy histogramu.
 */

bool createHistogram(char *inputFile, struct treeNode *histogram, enum argument arg);

int fileSize(FILE* file);

void prepareHistogram(struct treeNode *histogram);

void fillHistogram(FILE *file, struct treeNode *histogram);

int findHistogramSize(struct treeNode *histogram);

#endif