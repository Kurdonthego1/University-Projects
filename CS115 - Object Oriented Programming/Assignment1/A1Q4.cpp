// Name: Zana Osman
// Student Number: 200489300
// Date: September 20th, 2023
// Question 4

#include <iostream>

using namespace std;

// Declared functions
void OriginalArray(int array1[], int size);
void ReversedArray(int array1[], int array2[], int size);
void PrintArray(int array1[], int array2[], int size);

int main() {
  // Declare size and ask user for size aswell as inputs
  int size;

  cout << "Enter size of the array" << endl;
  cin >> size;

  int array1[size], array2[size];

  cout << "Please enter " << size << " integers, one at a time:" << endl;

  OriginalArray(array1, size);
  ReversedArray(array1, array2, size);

  PrintArray(array1, array2, size);

  return 0;
}

// Prints original array inputted by the user
void OriginalArray(int array1[], int size) {
  for (int i = 0; i < size; i++) {
    cin >> array1[i];
  }
}

// Reverses the array from the original array
void ReversedArray(int array1[], int array2[], int size) {
  for (int i = 0; i < size; i++) {
    array2[i] = array1[size - 1 - i];
  }
}

// Prints both the original array and the reversed array 
void PrintArray(int array1[], int array2[], int size) {
  cout << "Original Array:" << endl;
  for (int i = 0; i < size; i++) {
    cout << array1[i] << " ";
  }

  cout << endl;

  cout << "Reversed Array:" << endl;
  for (int i = 0; i < size; i++) {
    cout << array2[i] << " ";
  }

  cout << endl;
}
