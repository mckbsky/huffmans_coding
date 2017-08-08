#include "../headers/quicksort.h"

void quickSortChar(struct treeNode *histogram, int begin, int end) {
  int i = begin;
  int j = end;
  int middle;

  middle = histogram[(i + j) / 2].c;

  do {
    while(histogram[i].c < middle) {
      i++;
    }
    while(histogram[j].c > middle) {
      j--;
    }
    if(i <= j) {
      struct treeNode swap = histogram[i];
      histogram[i] = histogram[j];
      histogram[j] = swap;

      i++; j--;
    }
  }
  while(i <=j);

  if(begin < j) {
    quickSortChar(histogram, begin, j);
  }
  if(i < end) {
    quickSortChar(histogram, i, end);
  }
}

void quickSortFreq(struct treeNode *histogram, int begin, int end) {
  int i = begin;
  int j = end;
  int middle = histogram[(i + j) / 2].freq;

  do {
    while(histogram[i].freq > middle) {
      i++;
    }
    while(histogram[j].freq < middle) {
      j--;
    }
    if(i <= j) {
      struct treeNode swap = histogram[i];
      histogram[i] = histogram[j];
      histogram[j] = swap;

      i++; j--;
    }
  }
  while(i <= j);

  if(begin < j) {
    quickSortFreq(histogram, begin, j);
  }
  if(i < end) {
    quickSortFreq(histogram, i, end);
  }
}