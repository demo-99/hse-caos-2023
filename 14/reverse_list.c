#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void push(Node** head_ref, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void reverse(Node** head_ref) {
}

int main() {
    Node* head = NULL;

    push(&head, 20);
    push(&head, 15);
    push(&head, 10);
    push(&head, 5);

    // Print original list
    printf("Original List: \n");
    printList(head);

    reverse(&head);

    // Print reversed list
    printf("Reversed List: \n");
    printList(head);

    return 0;
}