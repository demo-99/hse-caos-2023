#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

// Два треда:
// 0 - ищет простые числа начиная с 2
// 1 - печатает простое число как только у нас находится новое. После печати count простых чисел завершаем исполение
// count получаем с stdin
int val = 2;
int count;
int latest_prime = 2;
bool finish = false;
int counter = 0;
std::condition_variable cv;
std::mutex mtx;

bool is_prime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void finding_primes()  {
    while (!finish) {
        if (is_prime(val)) {
            std::unique_lock<std::mutex> lock(mtx);
            latest_prime = val;
            cv.notify_one();
        }
        val++;
    }
}

void printing_primes() {
    while (counter <= count) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);
        std::cout << latest_prime << "\n";
        counter++;
        if (counter == count) {
            finish = true;
            cv.notify_all();
            return;
        }
    }
}

int main() {
    std::cin >> count;
    std::thread t1(finding_primes);
    std::thread t2(printing_primes);

    t1.join();
    t2.join();
}