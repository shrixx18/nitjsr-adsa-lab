// Implement the preorder traversal algorithm for binary trees without using recursion. 

#include<stdio.h>
#include<stdlib.h>  

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

void Non_recursive_preorder(struct Node* root) {
    if (root == NULL) return;
    struct Node** stack = (struct Node**)malloc(100 * sizeof(struct Node*));
    int top = -1;
    stack[++top] = root;
    while (top != -1) {
        struct Node* node = stack[top--];
        printf("%d ", node->data);
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
    free(stack);
}   

int main() {
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = 1;
    root->left = (struct Node*)malloc(sizeof(struct Node));
    root->left->data = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (struct Node*)malloc(sizeof(struct Node));
    root->right->data = 3;
    root->right->left = NULL;
    root->right->right = NULL;
    root->left->left = (struct Node*)malloc(sizeof(struct Node));
    root->left->left->data = 4;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->left->right = (struct Node*)malloc(sizeof(struct Node));
    root->left->right->data = 5;
    root->left->right->left = NULL;
    root->left->right->right = NULL;
    root->right->left = (struct Node*)malloc(sizeof(struct Node));
    root->right->left->data = 6;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = (struct Node*)malloc(sizeof(struct Node));
    root->right->right->data = 7;
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    printf("Preorder traversal of binary tree is: \n");
    Non_recursive_preorder(root);
    printf("\n");

    return 0;
}