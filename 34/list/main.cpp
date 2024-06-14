#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LockFreeSinglyLinkedList {
    std::atomic<Node*> atomic_head;

public:
    LockFreeSinglyLinkedList() : atomic_head(nullptr) {}

    void insert(int value) {
        Node *node = new Node(value);
        node->next = atomic_head.load();

        // std::atomic_compare_exchange_strong(atomic_head, &(node->next), node);
        while (!atomic_head.compare_exchange_weak(node->next, node, std::memory_order_relaxed));
    }

    void print() {
        size_t counter = 0;
        Node* current = atomic_head.load();
        Node* prev = nullptr;
        while (current != nullptr) {
            free(prev);
            ++counter;
            // std::cout << current->data << " -> ";
            prev = current;
            current = current->next;
        }
        // std::cout << "nullptr" << std::endl;
        std::cout << "sizeof(list): " << counter << std::endl;
    }
};

void insert_values(LockFreeSinglyLinkedList& list, int start, int end) {
    for (int i = start; i < end; ++i) {
        list.insert(i);
    }
}

int main() {
    LockFreeSinglyLinkedList list;

    const int num_threads = 12;
    const int values_per_thread = 100'000;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(insert_values, std::ref(list), i * values_per_thread, (i + 1) * values_per_thread));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    list.print();

    return 0;
}
