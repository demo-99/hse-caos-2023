#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_node(int val) {
    struct TreeNode* tree_ptr = malloc(sizeof(TreeNode));
    tree_ptr->left = NULL;
    tree_ptr->right = NULL;
    tree_ptr->value = val;
}

void insert(TreeNode** node, int val) {
    if (!node) {
        return;
    }
    if (!*node) {
        *node = create_node(val);
        return;
    }

    if (val < (*node)->value) {
        insert(&(*node)->left, val);
    } else {
        insert(&(*node)->right, val);
    }
}

void print_tree_in_order(TreeNode* node) {
    if (!node) {
        return;
    }

    print_tree_in_order(node->left);
    printf("%d ", node->value);
    print_tree_in_order(node->right);
}

void free_tree(TreeNode* node) {
    if (node) {
        free_tree(node->right);
        free_tree(node->left);
        free(node);
    }
}

int main() {
    TreeNode* root = NULL;

    insert(&root, 4);
    insert(&root, 2);
    insert(&root, 6);
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 5);
    insert(&root, 7);

    print_tree_in_order(root);
    printf("\n");

    free_tree(root);

    return 0;
}