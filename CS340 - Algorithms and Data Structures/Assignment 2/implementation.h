#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <iostream>
#include <vector>

// Making the class and having the private and public functions
class MinMax {
private:
    std::vector<int> heap;

    bool isEvenDepth(int index);
    void swap(int i, int j);
    void moveUp(int index);
    void moveUpMin(int index);
    void moveUpMax(int index);
    void moveDown(int index);
    void moveDownMin(int index);
    void moveDownMax(int index);

public:
    void buildHeap(std::vector<int> elements);
    int findMin();
    int findMax();
    void insertHeap(int value);
    int deleteMin();
    int deleteMax();
    void printHeap();
};

#endif
