#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>

void multithreaded_quicksort(std::vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    auto p = arr[high];
    auto lambda = [&](const int a) { return a < p;};
    auto d = std::partition(arr.begin() + low, arr.begin() + high, lambda);
    std::swap(*d, arr[high]);
    auto left = std::async(std::launch::async, [&]() {
        multithreaded_quicksort(arr, low, (d - arr.begin()) - 1);
    });
    auto right = std::async(std::launch::async, [&]() {
        multithreaded_quicksort(arr, (d - arr.begin()) + 1, high);
    });
    left.get();
    right.get();
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
