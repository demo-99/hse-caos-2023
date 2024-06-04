#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>

class Barrier {
public:
    Barrier(int numThreads) : numThreads(numThreads) {}

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        ++counter;
        if (counter != numThreads) {
            cv.wait(lock);
        } else {
            cv.notify_all();
        }
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int numThreads;
    int counter = 0;
};

std::mutex printer;

void worker(int id, Barrier& barrier) {
    printer.lock();
    std::cout << "Worker " << id << " is working" << std::endl;
    printer.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
    printer.lock();
    std::cout << "Worker " << id << " waiting at barrier" << std::endl;
    printer.unlock();
    barrier.wait();  // shoudl wait numThreads reached wait;
    printer.lock();
    std::cout << "Worker " << id << " passed the barrier" << std::endl;
    printer.unlock();
}

int main() {
    const int numThreads = 5;
    Barrier barrier(numThreads);
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, i, std::ref(barrier));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}