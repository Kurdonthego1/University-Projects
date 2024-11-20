#ifndef SORTS_H
#define SORTS_H

#include <vector>

// Function prototypes
int insertionSort(std::vector<int>& items);
int mergeSort(std::vector<int>& items, int first, int last);
int quickSort(std::vector<int>& items, int low, int high);
int quickInsertionSort(std::vector<int>& items, int low, int high, int k);

#endif // SORTS_H
