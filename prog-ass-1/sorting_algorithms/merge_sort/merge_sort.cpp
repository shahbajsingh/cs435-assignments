#include <chrono>
#include <iostream>
#include <vector>

/**
 * @brief Merge two subarrays of arr[].
 * 
 * @param arr 
 * @param l 
 * @param m 
 * @param r 
 */
void merge(int arr[], int const l, int const m, int const r) {
    int const subarr1 = m - l + 1; // size of left subarray
    int const subarr2 = r - m; // size of right subarray

    int L[subarr1], R[subarr2]; // create temp arrays

    // copy data to L[]
    for (int i = 0; i < subarr1; i++) {
        L[i] = arr[l + i];
    }

    // copy data to R[]
    for (int j = 0; j < subarr2; j++) {
        R[j] = arr[m + 1 + j];
    }

    // merge L[] and R[] back into arr[]

    int idx_l = 0; // initial index of left subarray
    int idx_r = 0; // initial index of right subarray
    int idx_m = l; // initial index of merged subarray

    while (idx_l < subarr1 && idx_r < subarr2) {
        if (L[idx_l] <= R[idx_r]) {
            arr[idx_m] = L[idx_l];
            idx_l++;
        } else {
            arr[idx_m] = R[idx_r];
            idx_r++;
        }
        idx_m++;
    }

    // copy any remaining elements of L[]
    while (idx_l < subarr1) {
        arr[idx_m] = L[idx_l];
        idx_l++;
        idx_m++;
    }

    // copy any remaining elements of R[]
    while (idx_r < subarr2) {
        arr[idx_m] = R[idx_r];
        idx_r++;
        idx_m++;
    }
}

/**
 * @brief Sorts an array using the merge sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param l The left index of the array.
 * @param r The right index of the array.
 */
void merge_sort(int arr[], int const l, int const r) {
    if (l >= r) {
        return;
    }

    int m = l + (r - l) / 2;
    
    // sort and merge two subarrays of arr[] recursively
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);
    merge(arr, l, m, r);
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
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Given array is \n";
    print_arr(arr, n);

    std::cout << "\n\n";

    std::cout << "Running merge sort...\n";
    merge_sort(arr, 0, n - 1);

    std::cout << "Sorted array is \n";
    print_arr(arr, n);

    std::cout << "\n\n";

    std::cout << "Measuring runtime of merge sort...\n";
    std::cout << "Average runtime: " << measure_runtime(merge_sort, arr, n, 100) << "ms\n";

    return 0;
}