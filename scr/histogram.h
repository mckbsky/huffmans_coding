#ifndef HISTOGRAM_H
#define HISTOGRAM_H

struct histTemplate {
  char c; //dana litera
  int occ; //ilość wystąpień
};

typedef struct hist_template histogram;
histogram *hArray[25];

/*
 * TODO: Mariusz - wypełnienie tablicy struktur kolejnymi literami i ustawienie
 * int occ na 0
 * NOTE: uwzględniać wielkośc liter?
 */

void prepareHistogram(histogram *hArray);

/*
 * TODO: Mariusz - funkcja otwiera plik tekstowy o nazwie podanej jako argument
 * wywołania i tworzy na jego podstawie histogram występowania poszczególnych
 * liter
 */
void createHistogram(char* filename, histogram *hArray);

/*
 * TODO: sortowanie względem ilości wystąpień danej litery
 * NOTE: początkowo może to być jakieś proste sortowanie, docelowo qsort
 */

void qsort(histogram *hArray);

#endif //histogram.h
