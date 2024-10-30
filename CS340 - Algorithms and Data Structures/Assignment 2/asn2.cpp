#include <iostream>
#include "implementation.h"

int main() {
    MinMax heap;
    
    // Numbers from the assignment tree
    std::vector<int> elements = {6, 81, 87, 14, 17, 71, 80, 12, 25, 52, 20, 28, 78, 31, 
                                 42, 31, 59, 16, 24, 79, 63, 18, 19, 32, 13, 15, 48};
    // The build function
    heap.buildHeap(elements);
    
    // Printing the min and max elements
    std::cout << "Min element: " << heap.findMin() << std::endl;
    std::cout << "Max element: " << heap.findMax() << std::endl;
    
    // Inserting an element into the heap
    int value;
    std::cout << "What element would you like to insert ";
    std::cin >> value;
    heap.insertHeap(value);
    std::cout << "After inserting " << value << ", Min: " << heap.findMin() << ", Max: " << heap.findMax() << std::endl;
    
    // Deleting the minimum element
    heap.deleteMin();
    std::cout << "After deleteMin, Min: " << heap.findMin() << std::endl;
    
    // Deleting the maximum element
    heap.deleteMax();
    std::cout << "After deleteMax, Max: " << heap.findMax() << std::endl;
    
    // Printing the final state of the heap
    std::cout << "Final heap: ";
    heap.printHeap();

    return 0;
}
