#include <iostream>
#include <vector>
#include <thread>
#include <future>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void multithreaded_quicksort(std::vector<int>& arr, int low, int high) {
    // TODO
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5, 3, 0, -10, 3, 5, 123, -123};
    int n = arr.size();

    multithreaded_quicksort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
