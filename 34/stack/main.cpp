#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>

template <typename T>
class LockFreeStack {
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    std::atomic<Node*> head;

public:
    LockFreeStack() : head(nullptr) {}

    void push(T value) {
    }

    bool pop(T& value) {
    }
};

void stack_pusher(LockFreeStack<int>& stack, int start, int end) {
    for (int i = start; i < end; ++i) {
        stack.push(i);
    }
}

void stack_popper(LockFreeStack<int>& stack, int count) {
    int value;
    for (int i = 0; i < count; ++i) {
        while (!stack.pop(value)) {}
        std::cout << "Popped: " << value << std::endl;
    }
}

int main() {
    LockFreeStack<int> stack;

    const int num_pushers = 2;
    const int num_poppers = 2;
    const int values_per_thread = 10;

    std::vector<std::thread> pushers, poppers;

    for (int i = 0; i < num_pushers; ++i) {
        pushers.emplace_back(stack_pusher, std::ref(stack), i * values_per_thread, (i + 1) * values_per_thread);
    }

    for (int i = 0; i < num_poppers; ++i) {
        poppers.emplace_back(stack_popper, std::ref(stack), values_per_thread * num_pushers / num_poppers);
    }

    for (auto& pusher : pushers) {
        pusher.join();
    }

    for (auto& popper : poppers) {
        popper.join();
    }

    return 0;
}
