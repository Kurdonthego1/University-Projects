// Name: Zana Osman
// Student Number: 200489300
// Date: April 2nd, 2024

#include <iostream>

using namespace std;

// Function to perform selection sort and count
// the number of operations it will take to sort the array
int SelectionSort(int Items[], int n) {
    int operations = 0;

    for(int i = 0; i < n - 1; ++i) {
        int MinIndex = i;
        for(int j = i + 1; j < n; ++j) {
            if(Items[j] < Items[MinIndex]) {
                MinIndex = j;
            }
            // Count is in the inner for loop this is because the inner loop
            // and if statement determine if it should be swapped
            // outer loop is used to increment to the next array index
            operations++;
        }
        // Swap and count another operation
        swap(Items[i], Items[MinIndex]);
        operations++;
    }
    
    // We return the count of operations and print it out in main
    return operations;
}

// Function to perform insertion sort and count
// the number of operations it will take to sort the array
int InsertionSort(int Items[], int n) {
    int operations = 0;
    int i, j, key;

    for (i = 1; i < n; ++i) {
        key = Items[i];
        j = i - 1;

        while (j >= 0 && Items[j] > key) {
            Items[j + 1] = Items[j];
            j--;
            // Increment by 2 as it will take the value out and copy into the next spot
            operations = operations + 2;
        }
        Items[j + 1] = key;
        // Increment by 1
        operations++;
    }

    // We return the count of operations and print it out in main
    return operations;
}

// Function for merging to subarrays and count
// the number of operations it will take to sort the array
int Merge(int Items[], int first, int middle, int last) {
    // Calculate the sizes of the subarrays
    int n1 = middle - first + 1;
    int n2 = last - middle;

    // Create temp arrays to hold the subarrays
    int L[n1], M[n2];

    // Initialize variables and operations count
    int i, j, k, operations;
    operations = 0;

    // Copy data from original array to the temp arrays
    for (i = 0; i < n1; ++i)
        L[i] = Items[first + i];
    for (j = 0; j < n2; ++j)
        M[j] = Items[middle + 1 + j];

    // Defined 0 to set up for merging the two subarrays
    // Must be after the two for loops or it will not function
    i = 0;
    j = 0;
    k = first;

    // Merge the two subarray back together
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            Items[k] = L[i];
            i++;
        } else {
            Items[k] = M[j];
            j++;
        }
        k++;
        // Count number of operations, will count comparisons and assignments each time they happen
        operations++;
    }

    // Any remaining elements will be copied from the left subarray
    while (i < n1) {
        Items[k] = L[i];
        i++;
        k++;
        // Increase operation count as long as there is remaining subarrays
        operations++;
    }

    // Any remaining elements will be copied from the right subarray
    while (j < n2) {
        Items[k] = M[j];
        j++;
        k++;
        // Increase operation count as long as there is remaining subarrays
        operations++;
    }

    // Returns the total number of operations during the entirety of the function
    return operations;
}

int MergeSort(int Items[], int first, int last){  
    // Set operation count to be 0
    int operations = 0;

    // Condition to allow for function to work, uses recursion
    if (first < last){
        int middle = (first + last) / 2;
        // Each time the functions are called, it will count operations and return
        operations += MergeSort(Items, first, middle);
        operations += MergeSort(Items, middle + 1, last);
        operations += Merge(Items, first, middle, last);
    }

    // Returns operations count within this function
    return operations;
}

int main(){
    // n for number of integer and elements for the integers
    int n;

    // Integer initializer
    cout << "Enter the number of integer elements: ";
    cin >> n;

    // Array initializer
    int Items[n];

    // Ask the user to enter the elements
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> Items[i];
    }

    // Copy so it resets
    int Items2[n], Items3[n];
    copy(Items, Items + n, Items2);
    copy(Items, Items + n, Items3);

    // Prints the SelectionSort results and operation counts
    int selection = SelectionSort(Items, n);
    cout << "\nSelectionSort results: ";
    for (int i = 0; i < n; ++i) {
        cout << Items[i] << " ";
    } cout << endl;
    cout << "Number of operations: " << selection << endl;

    // Prints the InsertionSort results and operation count'
    int insert = InsertionSort(Items2, n);
    cout << "\nInsertionSort results: ";
    for (int i = 0; i < n; ++i) {
        cout << Items2[i] << " ";
    } cout << endl;
    cout << "Number of operations: " << insert << endl;

    // Prints the MergeSort results and operation count
    int merge = MergeSort(Items3, 0, n - 1);
    cout << "\nMergeSort result: ";
    for (int i = 0; i < n; ++i) {
        cout << Items3[i] << " ";
    } cout << endl;
    cout << "Number of operations: " << merge << endl;

    return 0;
}
