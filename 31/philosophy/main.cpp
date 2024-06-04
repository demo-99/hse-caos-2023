#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

const int num_philosophers = 5;
std::mutex forks[num_philosophers];

void philosopher(int id) {
    while (true) {
        std::lock(forks[id], forks[(id + 1) % num_philosophers]);
        std::lock_guard<std::mutex> left(forks[id], std::adopt_lock);
        std::lock_guard<std::mutex> right(forks[(id + 1) % num_philosophers], std::adopt_lock);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // TODO: LOCK left and right forks;

        std::cout << "Philosopher " << id << " is eating." << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::vector<std::thread> philosophers;
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers.push_back(std::thread(philosopher, i));
    }

    for (auto& th : philosophers) {
        th.join();
    }

    return 0;
}
