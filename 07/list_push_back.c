#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

ListNode* push_back(ListNode* tail, int val) {
    // TODO: Write your code here

    return tail;
}

void print_list(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void free_list(ListNode* head) {
    ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    ListNode* head = NULL;
    ListNode* tail = NULL;

    tail = push_back(tail, 1);
    head = tail;
    tail = push_back(tail, 2);
    tail = push_back(tail, 3);

    print_list(head);

    free_list(head);

    return 0;
}
