#include "sorts.h"
#include <iostream>
#include <algorithm>

int insertionSort(std::vector<int>& items) {
    int operations = 0;
    for (int i = 1; i < items.size(); ++i) {
        int key = items[i];
        int j = i - 1;
        while (j >= 0 && items[j] > key) {
            items[j + 1] = items[j];
            j--;
            operations++;
        }
        items[j + 1] = key;
        operations++;
    }
    return operations;
}

// Merge sort and helper merge function
int merge(std::vector<int>& items, int first, int middle, int last) {
    int operations = 0;
    std::vector<int> left(items.begin() + first, items.begin() + middle + 1);
    std::vector<int> right(items.begin() + middle + 1, items.begin() + last + 1);

    int i = 0, j = 0, k = first;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            items[k++] = left[i++];
        } else {
            items[k++] = right[j++];
        }
        operations++;
    }
    while (i < left.size()) items[k++] = left[i++];
    while (j < right.size()) items[k++] = right[j++];
    return operations;
}

int mergeSort(std::vector<int>& items, int first, int last) {
    int operations = 0;
    if (first < last) {
        int middle = (first + last) / 2;
        operations += mergeSort(items, first, middle);
        operations += mergeSort(items, middle + 1, last);
        operations += merge(items, first, middle, last);
    }
    return operations;
}

// Quicksort and helper functions
int partition(std::vector<int>& items, int low, int high) {
    int pivot = items[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (items[j] <= pivot) {
            std::swap(items[++i], items[j]);
        }
    }
    std::swap(items[i + 1], items[high]);
    return i + 1;
}

int quickSort(std::vector<int>& items, int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);
        quickSort(items, low, pi - 1);
        quickSort(items, pi + 1, high);
    }
    return 0;
}

int quickInsertionSort(std::vector<int>& items, int low, int high, int k) {
    if (high - low + 1 < k) return 0;
    quickSort(items, low, high);
    return insertionSort(items);
}
