#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <map>

// --- INSERTION SORT ---

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
double measure_runtime_insertion(void (*func)(int[], int), int arr[], int n, int numIterations) {
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

// ------------------------




// --- SELECTION SORT ---

/**
 * @brief Sorts an array using the selection sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The size of the array.
 */
void selectio_sort(int arr[], int n){
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
double measure_runtime_selection(void (*func)(int[], int), int arr[], int n, int numIterations) {
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

// ------------------------




// --- MERGE SORT ---

/**
 * @brief Merge two subarrays of arr[].
 * 
 * @param arr The array to be sorted.
 * @param l Left index of the array.
 * @param m Middle index of the array.
 * @param r Right index of the array.
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
double measure_runtime_merge(void (*func)(int[], int, int), int arr[], int n, int numIterations) {
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

// ------------------------




// ---- BUBBLE SORT ----

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
double measure_runtime_bubble(void (*func)(int[], int), int arr[], int n, int numIterations) {
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

// ------------------------




// ---- QUICK SORT ----

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
double measure_runtime_quick(void (*func)(int[], int, int), int arr[], int n, int numIterations) {
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

// ------------------------



std::vector<int> gen_rand_arr(int size, int min, int max) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

std::vector<int> gen_increasing_rand_arr(int size, int step) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis(0, step);
    
    int current = 0;
    for (int i = 0; i < size; i++) {
        arr[i] = current + dis(gen);
        if ((i + 1) % step == 0) {
            current += step;
        }
    }
    
    return arr;
}

std::vector<int> gen_decreasing_rand_arr(int size, int step) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis(0, step);
    
    int current = step * size;
    for (int i = 0; i < size; i++) {
        arr[i] = current - dis(gen);
        if ((i + 1) % step == 0) {
            current -= step;
        }
    }
    
    return arr;
}

void print_arr(std::vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    // Random arrays
    std::vector<int> rand_arr_10 = gen_rand_arr(10, 0, 1000);
    std::vector<int> rand_arr_100 = gen_rand_arr(100, 0, 1000);
    std::vector<int> rand_arr_1k = gen_rand_arr(1000, 0, 1000);
    std::vector<int> rand_arr_1m = gen_rand_arr(1000000, 0, 1000);

    // Increasing arrays
    std::vector<int> incr_arr_10 = gen_increasing_rand_arr(10, 10);
    std::vector<int> incr_arr_100 = gen_increasing_rand_arr(100, 10);
    std::vector<int> incr_arr_1k = gen_increasing_rand_arr(1000, 10);
    std::vector<int> incr_arr_1m = gen_increasing_rand_arr(1000000, 10);

    // Decreasing arrays
    std::vector<int> decr_arr_10 = gen_decreasing_rand_arr(10, 10);
    std::vector<int> decr_arr_100 = gen_decreasing_rand_arr(100, 10);
    std::vector<int> decr_arr_1k = gen_decreasing_rand_arr(1000, 10);
    std::vector<int> decr_arr_1m = gen_decreasing_rand_arr(1000000, 10);

    // Measure runtime of sorting algorithms
    int numIterations = 1000; // for 10, 100, 1000
    int numIterations_1m = 1; // for 1m

    // Test random arrays
    std::cout << "Random arrays" << std::endl;
    std::cout << "Size: 10" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, rand_arr_10.data(), rand_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, rand_arr_10.data(), rand_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, rand_arr_10.data(), rand_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, rand_arr_10.data(), rand_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, rand_arr_10.data(), rand_arr_10.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 100" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, rand_arr_100.data(), rand_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, rand_arr_100.data(), rand_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, rand_arr_100.data(), rand_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, rand_arr_100.data(), rand_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, rand_arr_100.data(), rand_arr_100.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 1000" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, rand_arr_1k.data(), rand_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, rand_arr_1k.data(), rand_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, rand_arr_1k.data(), rand_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, rand_arr_1k.data(), rand_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, rand_arr_1k.data(), rand_arr_1k.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 1m" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, rand_arr_1m.data(), rand_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, rand_arr_1m.data(), rand_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, rand_arr_1m.data(), rand_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, rand_arr_1m.data(), rand_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, rand_arr_1m.data(), rand_arr_1m.size(), numIterations_1m) << " ms" << std::endl;

    // Test increasing arrays
    std::cout << "Increasing arrays" << std::endl;
    std::cout << "Size: 10" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, incr_arr_10.data(), incr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, incr_arr_10.data(), incr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, incr_arr_10.data(), incr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, incr_arr_10.data(), incr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, incr_arr_10.data(), incr_arr_10.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 100" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, incr_arr_100.data(), incr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, incr_arr_100.data(), incr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, incr_arr_100.data(), incr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, incr_arr_100.data(), incr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, incr_arr_100.data(), incr_arr_100.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 1000" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, incr_arr_1k.data(), incr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, incr_arr_1k.data(), incr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, incr_arr_1k.data(), incr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, incr_arr_1k.data(), incr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, incr_arr_1k.data(), incr_arr_1k.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 1m" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, incr_arr_1m.data(), incr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, incr_arr_1m.data(), incr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, incr_arr_1m.data(), incr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, incr_arr_1m.data(), incr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
   // std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, incr_arr_1m.data(), incr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;

    // Test decreasing arrays
    std::cout << "Decreasing arrays" << std::endl;
    std::cout << "Size: 10" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, decr_arr_10.data(), decr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, decr_arr_10.data(), decr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, decr_arr_10.data(), decr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, decr_arr_10.data(), decr_arr_10.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, decr_arr_10.data(), decr_arr_10.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 100" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, decr_arr_100.data(), decr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, decr_arr_100.data(), decr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, decr_arr_100.data(), decr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, decr_arr_100.data(), decr_arr_100.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, decr_arr_100.data(), decr_arr_100.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 1000" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, decr_arr_1k.data(), decr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, decr_arr_1k.data(), decr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, decr_arr_1k.data(), decr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, decr_arr_1k.data(), decr_arr_1k.size(), numIterations) << " ms" << std::endl;
    std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, decr_arr_1k.data(), decr_arr_1k.size(), numIterations) << " ms" << std::endl;

    std::cout << "Size: 1m" << std::endl;
    std::cout << "Insertion sort: " << measure_runtime_insertion(insertion_sort, decr_arr_1m.data(), decr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Selection sort: " << measure_runtime_selection(selectio_sort, decr_arr_1m.data(), decr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Merge sort: " << measure_runtime_merge(merge_sort, decr_arr_1m.data(), decr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    std::cout << "Bubble sort: " << measure_runtime_bubble(bubble_sort, decr_arr_1m.data(), decr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;
    // std::cout << "Quick sort: " << measure_runtime_quick(quick_sort, decr_arr_1m.data(), decr_arr_1m.size(), numIterations_1m) << " ms" << std::endl;

    return 0;
}


