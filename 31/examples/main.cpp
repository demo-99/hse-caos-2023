#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include <condition_variable>
#include <future>

using namespace std;

void thrfunc() {
    cout << "thrfunc\n";
}

int counter = 0;
mutex mtx;
std::condition_variable cv;
bool turn = true;

void increment() {
    for (int i = 0; i < 1000; ++i) {
        lock_guard<mutex> guard(mtx);
        ++counter;
    }
}

int sum(int n) {
    int result = 0;
    for (int i = 1; i <= n; ++i) {
        result += i;
    }
    return result;
}

void modify(string& s) {
    s += "Modified";
}

void printNumbers(int id) {
    for (int i = 1; i <= 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [id] { return (id == 1 && turn) || (id == 2 && !turn); });

        std::cout << "Thread " << id << ": " << i << std::endl;

        turn = !turn;
        cv.notify_all();
    }
}

int main() {
    thread thr1(thrfunc);
    thr1.join();

    thread thr2(increment);
    thread thr3(increment);

    thr2.join();
    thr3.join();

    cout << "Final counter value: " << counter << endl;

    future<int> result = async(launch::async, sum, 1'000'000);
    cout << "Sum from 1 to 1,000,000 is: " << result.get() << endl;

    string str("String from main. ");

    thread thr4(modify, ref(str));
    thr4.join();

    cout << "After modify: " << str << endl;

    thread thr5(printNumbers, 1);
    thread thr6(printNumbers, 2);

    thr5.join();
    thr6.join();

    promise<int> p;
    future<int> f = p.get_future();

    thread thr7([&p]() {p.set_value(1);});
    cout << "Got future result: " << f.get() << endl;
    thr7.join();
}
