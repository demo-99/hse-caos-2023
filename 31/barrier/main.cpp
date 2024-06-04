#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

const int num_threads = 5;
std::mutex mtx;
std::condition_variable cv;
int arrived = 0;

void barrier_point(int id) {

}

int main() {
    std::vector<std::thread>
    threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(barrier_point, i));
    }

    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
