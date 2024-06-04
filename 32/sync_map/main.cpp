#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <string>
#include <cassert>

template <typename K, typename V>
class SyncMap {
public:
    void insert(const K& key, const V& value) {
        map[key] = value;
    }

    void remove(const K& key) {
        map.erase(key);
    }

    bool find(const K& key, V& value) {
        auto it = map.find(key);
        if (it != map.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    size_t size() const {
        return map.size();
    }

private:
    std::unordered_map<K, V> map;
    mutable std::mutex mtx;
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
        std::cout << "Thread " << threadId << (found ? " found " : " did not find ") << "key " << key << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void removeValues(SyncMap<int, std::string>& syncMap, int threadId) {
    for (const auto& [key, value] : testData) {
        syncMap.remove(key);
        std::cout << "Thread " << threadId << " removed key " << key << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void validateMapSize(SyncMap<int, std::string>& syncMap, size_t expectedSize) {
    assert(syncMap.size() == expectedSize);
    std::cout << "Validation passed: expected size " << expectedSize << std::endl;
    std::cout << "Current map size: " << syncMap.size() << std::endl;
}

int main() {
    SyncMap<int, std::string> syncMap;

    std::vector<std::thread> insertThreads;
    std::vector<std::thread> findThreads;
    std::vector<std::thread> removeThreads;

    // Create threads to insert values
    for (int i = 0; i < 2; ++i) {
        insertThreads.emplace_back(insertValues, std::ref(syncMap), i);
    }

    // Create threads to find values
    for (int i = 0; i < 2; ++i) {
        findThreads.emplace_back(findValues, std::ref(syncMap), i);
    }

    // Join insertion threads
    for (auto& thread : insertThreads) {
        thread.join();
    }

    // Validate that all values are present
    validateMapSize(syncMap, testData.size());

    // Join find threads
    for (auto& thread : findThreads) {
        thread.join();
    }

    // Create threads to remove values
    for (int i = 0; i < 2; ++i) {
        removeThreads.emplace_back(removeValues, std::ref(syncMap), i);
    }

    // Join removal threads
    for (auto& thread : removeThreads) {
        thread.join();
    }

    // Validate that the map is empty
    validateMapSize(syncMap, 0);

    return 0;
}