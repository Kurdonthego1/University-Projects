// Name: Zana Osman
// Student Number: 200489300
// Date: September 18th, 2023
// Question 3

#include <iostream>

using namespace std;

// Declared Functions
void Collect(int ArrayCollect[], int size);
void Reorganize(int ArrayReorganize[], int size);
void ZigZag(int ArrayZigZag[], int size);

int main() {
  // Ask user for size of array and input
  int size;
  cout << "Please enter the size of the array:" << endl;
  cin >> size;
    
  int array[size];
    
  Collect(array, size);
  Reorganize(array, size);
  ZigZag(array, size);
  return 0;
}

// Function to collect the array elements, outputs the original array inputted by user
void Collect(int ArrayCollect[], int size) {
  cout << "Please enter " << size << " elements for your array" << endl << "Do not enter any repeats, only one of each number" << endl;
  for (int i = 0; i < size; i++) {
    cin >> ArrayCollect[i];
  }
  cout << "Original Array: ";
  for (int i = 0; i < size; i++) {
    cout << ArrayCollect[i] << " ";
  }
  cout << endl;
}

// Function to reorganize array, uses bubble sort to sort array in ascending order, then outputs the reorganized array
void Reorganize(int ArrayReorganize[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (ArrayReorganize[j] > ArrayReorganize[j + 1]) {
        int temp = ArrayReorganize[j];
        ArrayReorganize[j] = ArrayReorganize[j + 1];
        ArrayReorganize[j + 1] = temp;
      }
    }
  }
  cout << "Reorganized Array:" << endl;
  for (int i = 0; i < size; i++) {
    cout << ArrayReorganize[i] << "\t";
  }
  cout << endl;
}

// Function to zigzag array, with the reorganized array, every even 'position' is swapped with the next position. This allows for 0 fails and each position in an even spot is always bigger then the adjacent. (Only will fail if two of the same number is inputted), then outputs the zig zagged array.
void ZigZag(int ArrayZigZag[], int size) {
  for (int i = 0; i < size - 1; i++) {
    if (i % 2 == 0) {
      if (ArrayZigZag[i] > ArrayZigZag[i + 1]) {
        swap(ArrayZigZag[i], ArrayZigZag[i + 1]);
      }
    } else {
      if (ArrayZigZag[i] < ArrayZigZag[i + 1]) {
        swap(ArrayZigZag[i], ArrayZigZag[i + 1]);
      }
    }
  }
  cout << "Zig Zag Array:" << endl;
  for (int i = 0; i < size; i++) {
    cout << ArrayZigZag[i] << "\t";
  }
  cout << endl;
}