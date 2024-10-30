#include "implementation.h"
// Algorithm swap and max, cmath is for the depth calculation
#include <algorithm>
#include <cmath>

// Function to determine if the node at a given index is at an even depth
bool MinMax::isEvenDepth(int index) {
    int depth = 0;
    int nodeindex = index + 1;
    while (nodeindex > 1) {
        nodeindex >>= 1;
        depth++;
    }
     // Return true if depth is even, if not then return false
    return depth % 2 == 0;
}

// Function to swap two elements in the heap
void MinMax::swap(int i, int j) {
    std::swap(heap[i], heap[j]);
}

// Function to push up the element at the given index to its correct position
void MinMax::moveUp(int index) {
    // Base case: root node has no parent
    if (index == 0) return; 

    int parent = (index - 1) / 2;
    if (isEvenDepth(index)) {
        if (heap[index] > heap[parent]) {
            // Swap with parent if greater
            swap(index, parent); 
            moveUpMax(parent);
        } else {
            moveUpMin(index); 
        }
    } else {  
        // Node is at max level
        if (heap[index] < heap[parent]) {
            swap(index, parent); 
            // Swap with parent if smaller
            moveUpMin(parent);
        } else {
            moveUpMax(index);
        }
    }
}

// Function to push up in min levels (even depths)
void MinMax::moveUpMin(int index) {
    // Calculate grandparent index
    int grandparent = (index - 3) / 4;
    if (grandparent >= 0 && heap[index] < heap[grandparent]) {
        // Swap with grandparent if smaller
        swap(index, grandparent); 
        moveUpMin(grandparent);
    }
}

// Function to push up in max levels (odd depths)
void MinMax::moveUpMax(int index) {
    int grandparent = (index - 3) / 4;
    if (grandparent >= 0 && heap[index] > heap[grandparent]) {
        swap(index, grandparent);
        moveUpMax(grandparent);
    }
}

// Function to push down the element at the given index to its correct position
void MinMax::moveDown(int index) {
    if (isEvenDepth(index)) {
        moveDownMin(index);
    } else {
        moveDownMax(index);
    }
}

// Function to push down in min levels (even depths)
void MinMax::moveDownMin(int index) {
    int smallest = index;
    // Left child index
    int left = 2 * index + 1;    
    // Right child index
    int right = 2 * index + 2;

    // Check if left child exists and is smaller
    if (left < heap.size() && heap[left] < heap[smallest])
        smallest = left;
    // Check if right child exists and is smaller
    if (right < heap.size() && heap[right] < heap[smallest])
        smallest = right;

    // Check grandchildren
    for (int i = 2 * left + 1; i <= 2 * right + 2 && i < heap.size(); ++i) {
        if (heap[i] < heap[smallest])
            smallest = i;
    }

    if (smallest != index) {
        swap(index, smallest);
        if (smallest > 2 * index + 2) {
            int parent = (smallest - 1) / 2;
            if (heap[smallest] > heap[parent])
                swap(smallest, parent);
            // This is for a recursive moveDown, it is the same for all the others adjusted to there case
            moveDownMin(smallest);
        }
    }
}

// Function to push down in max levels (odd depths)
void MinMax::moveDownMax(int index) {
    int largest = index;
    int left = 2 * index + 1;    // Left child index
    int right = 2 * index + 2;   // Right child index

    // Check if left child exists and is larger
    if (left < heap.size() && heap[left] > heap[largest])
        largest = left;
    // Check if right child exists and is larger
    if (right < heap.size() && heap[right] > heap[largest])
        largest = right;

    // Check grandchildren
    for (int i = 2 * left + 1; i <= 2 * right + 2 && i < heap.size(); ++i) {
        if (heap[i] > heap[largest])
            largest = i;
    }

    if (largest != index) {
        swap(index, largest);
        if (largest > 2 * index + 2) { 
        // Calculate parent of swapped node
            int parent = (largest - 1) / 2; 
            if (heap[largest] < heap[parent])
                swap(largest, parent);   
            moveDownMax(largest);        
        }
    }
}

// Function to build the min-max heap from a list of elements
void MinMax::buildHeap(std::vector<int> elements) {
    heap = elements;
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        moveDown(i);
    }
}

// Function to find the minimum element (at the root)
int MinMax::findMin() {
    if (heap.empty()) return -1;
    return heap[0];               
}

// Function to find the maximum element (among the first two levels)
int MinMax::findMax() {
    // Return -1 if heap is empty
    if (heap.empty()) return -1;  
    // Only one element exists
    if (heap.size() == 1) return heap[0];
    // Two elements, max is at index 1
    if (heap.size() == 2) return heap[1]; 
    return std::max(heap[1], heap[2]);
}

// Function to insert a new value into the heap
void MinMax::insertHeap(int value) {
    heap.push_back(value);
    moveUp(heap.size() - 1);
}

// Function to delete the minimum element (root)
int MinMax::deleteMin() {
    // Return -1 if heap is empty
    if (heap.empty()) return -1;      
    int minElement = heap[0];       
    heap[0] = heap.back();     
    // Remove the last element     
    heap.pop_back();                  
    if (!heap.empty()) moveDown(0);
    return minElement;
}

// Function to delete the maximum element
int MinMax::deleteMax() {
    // Return -1 if heap is empty
    if (heap.empty()) return -1;
    // Case for if only one element is there
    if (heap.size() == 1) {
        int maxElement = heap.back();
        heap.pop_back();
        return maxElement;
    }
    // Determine index of maximum element (either at index 1 or 2)
    int maxIndex = (heap.size() == 2 || heap[1] > heap[2]) ? 1 : 2;
    int maxElement = heap[maxIndex];
    heap[maxIndex] = heap.back();
    // Removing last element
    heap.pop_back();                  
    if (maxIndex < heap.size())
        moveDown(maxIndex);
    return maxElement;
}

void MinMax::printHeap() {
    for (int val : heap) {
        // Printing each element in the heap
        std::cout << val << " ";      
    }
    std::cout << std::endl;
}
