#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include <condition_variable>
#include <future>
#include <array>

std::array<double, 3> arr;

// создать 3 треда:
//  0 - arr[0] += 100; arr[1] -= 101;
//  1 - arr[1] += 200; arr[2] -= 201;
//  2 - arr[2] += 300; arr[0] -= 301;
// Каждый тред должен отработать 100000
// после завершения всех тредов распечатать результат в main

int modify(int idx) {

}

int main() {
    std::thread thr[3];
    for (int i = 0; i < 3; i++) {
        thr[i] = std::thread(modify, i);
    }

    for (int i = 0; i < 3; i++) {

    }
}