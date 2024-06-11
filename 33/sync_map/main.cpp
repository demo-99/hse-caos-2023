#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <string>
#include <cassert>
#include <sstream>
#include <atomic>
#include <condition_variable>



template <typename K, typename V>
class SyncMap {
public:
    SyncMap() {
        counter = 0;
    }

    void insert(const K& key, const V& value) {
        std::unique_lock<std::mutex> lock(mutex);
        condvar.wait(lock, [this]() {return !counter; });
        map[key] = value;
    }

    void remove(const K& key) {
        std::unique_lock<std::mutex> lock(mutex);
        condvar.wait(lock, [this]() {return !counter; });
        map.erase(key);
    }

    bool find(const K& key, V& value) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            ++counter;
            std::cout << counter << std::endl;
        }

        auto it = map.find(key);
        if (it != map.end()) {
            value = it->second;
            --counter;
            condvar.notify_all();
            return true;
        }
        --counter;
        condvar.notify_all();
        return false;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return map.size();
    }

private:
    std::condition_variable condvar;
    mutable std::mutex mutex;
    std::unordered_map<K, V> map;
    std::atomic<int> counter;
};

const std::vector<std::pair<int, std::string>> testData = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"},
    {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"},
    {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"},
    {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"},
    {19, "nineteen"}, {20, "twenty"}
};

void insertValues(SyncMap<int, std::string>& syncMap, int threadId) {
    for (const auto& [key, value] : testData) {
        syncMap.insert(key, value + " by thread " + std::to_string(threadId));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void findValues(SyncMap<int, std::string>& syncMap, int threadId) {
    for (const auto& [key, value] : testData) {
        std::string foundValue;
        bool found = syncMap.find(key, foundValue);
        std::stringstream ss;
        ss << "Thread " << threadId << (found ? " found " : " did not find ") << "key " << key << std::endl;
        std::cout << ss.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void removeValues(SyncMap<int, std::string>& syncMap, int threadId) {
    for (const auto& [key, value] : testData) {
        syncMap.remove(key);
        std::stringstream ss;
        ss << "Thread " << threadId << " removed key " << key << std::endl;
        std::cout << ss.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void validateMapSize(SyncMap<int, std::string>& syncMap, size_t expectedSize) {
    std::stringstream ss;
    ss << "Expected map size " << expectedSize << std::endl;
    ss << "Current map size: " << syncMap.size() << std::endl;
    std::cout << ss.str();
    assert(syncMap.size() == expectedSize);
}

int main() {
    SyncMap<int, std::string> syncMap;

    std::vector<std::thread> insertThreads;
    std::vector<std::thread> findThreads;
    std::vector<std::thread> removeThreads;

    for (int i = 0; i < 2; ++i) {
        insertThreads.emplace_back(insertValues, std::ref(syncMap), i);
    }

    for (auto& thread : insertThreads) {
        thread.join();
    }

    for (int i = 0; i < 2; ++i) {
        findThreads.emplace_back(findValues, std::ref(syncMap), i);
    }

    validateMapSize(syncMap, testData.size());

    for (auto& thread : findThreads) {
        thread.join();
    }

    for (int i = 0; i < 2; ++i) {
        removeThreads.emplace_back(removeValues, std::ref(syncMap), i);
    }

    for (auto& thread : removeThreads) {
        thread.join();
    }

    validateMapSize(syncMap, 0);

    return 0;
}