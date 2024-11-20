#include "sorts.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

void displayArray(const vector<int>& arr) {
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Function to generate a random array of given size
vector<int> generateArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // Generates random integers between 0 and 999
    }
    return arr;
}

int main() {
    int n, k;
    cout << "Enter the number of elements (N): ";
    cin >> n;
    cout << "Enter the threshold for Quick-insertion (K): ";
    cin >> k;

    vector<int> items = generateArray(n);

    // Display original array if size <= 40
    if (n <= 40) {
        cout << "\nOriginal array:\n";
        displayArray(items);
        cout << "\n";
    }

    // Arrays to store the sorted results and corresponding running times
    vector<int> itemsCopy;
    double duration;
    vector<pair<string, double>> timings; // stores method name and running time

    // Insertion Sort
    itemsCopy = items;
    auto start = chrono::high_resolution_clock::now();
    insertionSort(itemsCopy);
    auto end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, milli>(end - start).count();
    timings.push_back({"Insertion Sort", duration});
    if (n <= 40) {
        cout << "Insertion Sort result:\n";
        displayArray(itemsCopy);
        cout << "\n";
    }

    // Merge Sort
    itemsCopy = items;
    start = chrono::high_resolution_clock::now();
    mergeSort(itemsCopy, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, milli>(end - start).count();
    timings.push_back({"Merge Sort", duration});
    if (n <= 40) {
        cout << "Merge Sort result:\n";
        displayArray(itemsCopy);
        cout << "\n";
    }

    // Quick Sort
    itemsCopy = items;
    start = chrono::high_resolution_clock::now();
    quickSort(itemsCopy, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, milli>(end - start).count();
    timings.push_back({"Quick Sort", duration});
    if (n <= 40) {
        cout << "Quick Sort result:\n";
        displayArray(itemsCopy);
        cout << "\n";
    }

    // Quick-Insertion Sort
    itemsCopy = items;
    start = chrono::high_resolution_clock::now();
    quickInsertionSort(itemsCopy, 0, n - 1, k);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, milli>(end - start).count();
    timings.push_back({"Quick-Insertion Sort", duration});
    if (n <= 40) {
        cout << "Quick-Insertion Sort result:\n";
        displayArray(itemsCopy);
        cout << "\n";
    }

    // Display timing table
    cout << "\n+---------------------+--------------------+\n";
    cout << "| Sorting Algorithm   | Running Time (ms)  |\n";
    cout << "+---------------------+--------------------+\n";
    for (const auto& timing : timings) {
        cout << "| " << setw(20) << left << timing.first 
                  << "| " << setw(18) << right << timing.second << " ms |\n";
    }
    cout << "+---------------------+--------------------+\n";

    return 0;
}
