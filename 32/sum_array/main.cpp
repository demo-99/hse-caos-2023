#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <numeric>


void subSum(const std::vector<int>& vec, int start, int end, int& sum) {
    int local_sum = 0;
    for (int i = start; i < end; ++i) {
        local_sum += vec[i];
    }
    sum = local_sum;
}

int parallelSum(const std::vector<int>& vec, int start, int end) {
    int sum = 0;
    int count = std::thread::hardware_concurrency();
    int d = vec.size() / count;
    std::vector<std::thread> v;
    std::vector<int> sums(count);
    int j = 0;
    for (int i = 0; i < end; i += d) {
        v.emplace_back(std::thread(subSum, vec, i, std::min(i + d, end), std::ref(sums[j])));
        ++j;
    }
    for (int i = 0; i < v.size(); ++i) {
        v[i].join();
    }
    for (int i = 0; i < v.size(); ++i) {
        sum += sums[i];
    }
    return sum;
}

int main() {
    std::vector<int> vec(1000000, 1); // Vector of 1 million elements, all set to 1
    auto start = std::chrono::high_resolution_clock::now();
    int sum = parallelSum(vec, 0, vec.size());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Total Sum: " << sum << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
