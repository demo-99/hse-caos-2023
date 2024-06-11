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
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(value);
        cond_var.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.wait(lock, [this](){return !queue.empty(); });
        if (queue.empty())
            return false;
        value = queue.front();
        queue.pop();
        return true;
    }

    bool empty() const {
        std::unique_lock<std::mutex> lock(mutex);
        return queue.empty();
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
