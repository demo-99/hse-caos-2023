#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int active_readers = 0;
bool writer_active = false;
int shared_data = 0;

void readerFunction(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (writer_active) {
            cv.wait(lock);
        }
        active_readers++;
        lock.unlock();

        std::cout << "Reader with id: " << id << " is reading " << shared_data << "\n";
        lock.lock();
        active_readers--;
        if (!active_readers) {
            cv.notify_all();
        }
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between reads
    }
}

void writerFunction(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (!writer_active && !active_readers) {
            cv.wait(lock);
        }
        writer_active = true;

        shared_data = id;
        std::cout << "Writer with id: " << id << " is writing " << shared_data << "\n";

        cv.notify_all();
        writer_active = false;
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Simulate time between writes
    }
}

int main() {
    const int num_readers = 5;
    const int num_writers = 2;
    std::vector<std::thread> readers, writers;

    for (int i = 1; i <= num_readers; ++i) {
        readers.push_back(std::thread(readerFunction, i));
    }

    for (int i = 1; i <= num_writers; ++i) {
        writers.push_back(std::thread(writerFunction, i));
    }

    for (auto& th : readers) {
        th.join();
    }

    for (auto& th : writers) {
        th.join();
    }

    return 0;
}
