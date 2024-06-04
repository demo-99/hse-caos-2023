#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>

std::unordered_map<std::string, int> wordCount;
std::mutex mtx;

void countWords(const std::string& text) {
    std::string word = "";
    for (char c : text) {
        if (c != ' ') {
            word.push_back(c);
        } else {
            std::unique_lock<std::mutex> lock(mtx);
            ++wordCount[word];
            word = "";
        }
    }
}

void processFilePart(const std::string& fileName, std::streampos start, std::streampos end) {
    std::ifstream file(fileName);
    if (!file.is_open()) return;

    file.seekg(start);
    std::string text;
    std::string line;
    while (file.tellg() < end && std::getline(file, line)) {
        text += line + " ";
    }

    countWords(text);
}

int main() {
    const std::string fileName = "large_text_file.txt";
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::streampos partSize = fileSize / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        std::streampos start = i * partSize;
        std::streampos end = (i == numThreads - 1) ? fileSize : start + partSize;
        threads.emplace_back(processFilePart, fileName, start, end);
    }

    for (auto& th : threads) {
        th.join();
    }

    for (const auto& [word, count] : wordCount) {
        std::cout << word << ": " << count << std::endl;
    }
    std::cout << wordCount.size() << std::endl;

    return 0;
}
