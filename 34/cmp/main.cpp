#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <cassert>

std::atomic<int> x, y, z;

void write_x() {
    x.store(1, std::memory_order_release);
}
void write_y() {
    y.store(1, std::memory_order_release);
}

void read_y_than_x() {
    while (!y.load(std::memory_order_acquire)) {}

    if (x.load(std::memory_order_acquire)) {
        ++z;
    }
}

void read_x_than_y() {
    while (!x.load(std::memory_order_acquire)) {}

    if (y.load(std::memory_order_acquire)) {
        ++z;
    }
}

int main() {
    std::atomic<int> shared_value(10);

    std::thread t1(write_x);
    std::thread t2(write_y);
    std::thread t3(read_y_than_x);
    std::thread t4(read_x_than_y);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    assert(z != 0);

    std::cout << "Success" << std::endl;

    return 0;
}
