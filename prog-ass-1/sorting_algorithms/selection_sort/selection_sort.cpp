#include <chrono>
#include <iostream>
#include <vector>
#include "selection_sort.h"

/**
 * @brief Sorts an array using the selection sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The size of the array.
 */
void selection_sort(int arr[], int n){
    int i, j, min_idx;

    // iterate arr[]
    for (i = 0; i < n-1; i++){
        // find min_idx of unsorted arr[i,...,n-1]
        min_idx = i;
        for (j = i+1; j < n; j++){
            if (arr[j] < arr[min_idx]){
                min_idx = j;
            }
        }

        // swap arr[min_idx] and arr[i]
        std::swap(arr[min_idx], arr[i]);
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
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);

    std::cout << "Original array: ";
    print_arr(arr, n);
    std::cout << std::endl;

    selection_sort(arr, n);

    std::cout << "Sorted array: ";
    print_arr(arr, n);
    std::cout << std::endl;

    std::cout << "Average runtime: " << measure_runtime(selection_sort, arr, n, 100) << " ms" << std::endl;

    return 0;
}