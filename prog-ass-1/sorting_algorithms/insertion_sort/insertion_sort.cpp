#include <chrono>
#include <iostream>
#include <vector>
#include "insertion_sort.h"

/**
 * @brief Sorts an array using the insertion sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The size of the array.
 */
void insertion_sort(int arr[], int n){
    int i, key, j;

    // for each element in arr
    for (i=1; i < n; i++){
        key = arr[i];
        j = i-1;

        // move elements of arr[0,...,i-1] > key
        // forward by one position

        while (j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j = j-1;
        }

        arr[j+1] = key;
    }
}

/**
 * @brief Measures the average runtime of a function.
 * 
 * @param func The function to be timed.
 * @param arr The array to be sorted.
 * @param n The size of the array.
 * @param numIterations The number of iterations to measure the runtime.
 * @return The average runtime of the function in milliseconds.
 */
double measure_runtime(void (*func)(int[], int), int arr[], int n, int numIterations) {
    double totalRuntime = 0.0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; i++) {
        func(arr, n);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    totalRuntime += duration.count();

    return totalRuntime / numIterations;
}

/**
 * @brief Print an array.
 * 
 * @param arr The array to be printed.
 * @param n The size of the array.
 */
void print_arr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {5, 2, 8, 12, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Before sorting: ";
    print_arr(arr, n);

    insertion_sort(arr, n);

    std::cout << "After sorting: ";
    print_arr(arr, n);

    std::cout << "Average runtime: " << measure_runtime(insertion_sort, arr, n, 1000000) << " ms" << std::endl;

    
    return 0;
}


