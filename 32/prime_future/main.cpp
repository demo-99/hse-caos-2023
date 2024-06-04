#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>

// Два треда:
// 0 - ищет простые числа начиная с 2
// 1 - печатает простое число как только у нас находится новое. После печати count простых чисел завершаем исполение
// count получаем с stdin
int val = 2;
int count;
int latest_prime = 2;
std::vector<std::promise<int>> p;
std::vector<std::future<int>> f;

bool is_prime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void finding_primes()  {
    int local_counter = 0;
    while (local_counter < count) {
        if (is_prime(val)) {
            p[local_counter].set_value(val);
            latest_prime = val;
            local_counter++;
        }
        val++;
    }
}

void printing_primes() {
    int local_counter = 0;
    while (local_counter < count) {
        latest_prime = f[local_counter].get();
        std::cout << latest_prime << "\n";
        local_counter++;
    }
}

int main() {
    std::cin >> count;
    f.resize(count);
    p.resize(count);
    for (int i = 0; i < count; ++i) {
        f[i] = p[i].get_future();
    }
    std::thread t1(finding_primes);
    std::thread t2(printing_primes);

    t1.join();
    t2.join();
}