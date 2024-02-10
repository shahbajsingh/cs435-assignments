#include <chrono>
#include <iostream>
#include <vector>

/**
 * @brief Partitions the array and returns the pivot index.
 * 
 * @param arr The array to be sorted.
 * @param start The start index of the array.
 * @param end The end index of the array.
 * @return int The pivot index.
 */
int partition(int arr[], int start, int end){

    int pivot = arr[start];
    int count = 0;

    for (int i = start + 1; i <= end; i++){
        if (arr[i] <= pivot)
            count++;
    }

    int pivot_idx = start + count;
    std::swap(arr[pivot_idx], arr[start]);

    int i = start, j = end-1;

    while (i < pivot_idx && j > pivot_idx){
        while (arr[i] <= pivot)
            i++;

        while (arr[j] > pivot)
            j--;

        if (i < pivot && j > pivot)
            std::swap(arr[i++], arr[j--]);
    }
    return pivot_idx;
}

void quick_sort(int arr[], int start, int end){
    if (start >= end) // base case
        return;

    int pivot = partition(arr, start, end);
    quick_sort(arr, start, pivot-1);
    quick_sort(arr, pivot+1, end);
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
double measure_runtime(void (*func)(int[], int, int), int arr[], int n, int numIterations) {
    double totalRuntime = 0.0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; i++) {
        func(arr, 0, n - 1);
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

    double runtime = measure_runtime(quick_sort, arr, n, numIterations);
    std::cout << "Sorted array: ";
    print_arr(arr, n);
    std::cout << std::endl;

    std::cout << "Average runtime: " << runtime << " ms" << std::endl;

    return 0;
}