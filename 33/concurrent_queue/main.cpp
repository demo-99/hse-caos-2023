#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <chrono>
#include <sstream>

template<typename T>
class ConcurrentQueue {
public:
    void push(T value) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    bool pop(T& value) {
    }

    bool empty() const {
    }

private:
    mutable std::mutex mutex;
    std::queue<T> queue;
    std::condition_variable cond_var;
};

int main() {
    ConcurrentQueue<int> queue;

    std::thread producer([&queue](){
        for (int i = 0; i < 10; ++i) {
            queue.push(i);
        }
    });

    std::thread consumer([&queue](){
        int value;
        for (int i = 0; i < 10; ++i) {
            queue.pop(value);
            std::stringstream ss;
            ss << "Consumed: " << value << std::endl;
            std::cout << ss.str();
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
