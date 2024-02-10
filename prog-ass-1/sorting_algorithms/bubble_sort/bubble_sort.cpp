#include <chrono>
#include <iostream>
#include <vector>
#include "bubble_sort.h"

/**
 * @brief Sorts an array using the bubble sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The size of the array.
 */
void bubble_sort(int arr[], int n){
    for (int i=0; i < n-1; i++){
        for (int j=0; j < n-i-1; j++){
            if (arr[j] > arr[j+1]){
                std::swap(arr[j], arr[j+1]);
            }
        }
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    int numIterations = 1000;

    std::cout << "Original array: ";
    print_arr(arr, n);
    std::cout << std::endl;

    double runtime = measure_runtime(bubble_sort, arr, n, numIterations);
    std::cout << "Sorted array: ";
    print_arr(arr, n);
    std::cout << std::endl;
    std::cout << "Average runtime: " << runtime << " ms" << std::endl;

    return 0;
}
