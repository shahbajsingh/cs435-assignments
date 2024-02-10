#include "../insertion_sort/insertion_sort.h"
#include "../selection_sort/selection_sort.h"
#include "../merge_sort/merge_sort.h"
#include "../bubble_sort/bubble_sort.h"
#include "../quick_sort/quick_sort.h"

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

// Function to generate a random array given size and maximum value
std::vector<int> generateRandomArray(int size, int maxVal) {
    std::vector<int> arr(size);
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, maxVal); // Define the range

    for (int& i : arr) {
        i = distr(gen); // Generate a random number within the range
    }

    return arr;
}

// Function to print the array (for testing purposes)
void printArray(const std::vector<int>& arr) {
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main() {
    // Sizes and their respective maximum values
    std::vector<int> sizes = {10, 100, 10000, 1000000};
    std::vector<int> maxValues = {10, 100, 10000, 1000000};

    // Generate and print random arrays
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::vector<int> randomArray = generateRandomArray(sizes[i], maxValues[i]);
        std::cout << "Random array of size " << sizes[i] << " (showing first 10 values): \n";
        printArray(std::vector<int>(randomArray.begin(), randomArray.begin() + std::min(10, static_cast<int>(randomArray.size()))));
    }

    return 0;
}

