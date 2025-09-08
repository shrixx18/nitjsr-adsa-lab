// Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL
// trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees.

#include <stdio.h>
#include <stdlib.h>

// A structure for a single node in the AVL tree
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get the height of a node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return(node);
}

// Right rotate subtree rooted with y
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Function to insert a key into the AVL tree
struct Node* insertItem(struct Node* node, int key) {
    // 1. Perform the normal BST insertion
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor and check for imbalance
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to find the node with the minimum value
struct Node * minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a key from the AVL tree
struct Node* deleteItem(struct Node* root, int key) {
    // 1. Perform standard BST deletion
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else { // Node with key to be deleted is found
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // 2. Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Get the balance factor and rebalance if needed
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for an item in the AVL tree
struct Node* searchItem(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return searchItem(root->right, key);

    return searchItem(root->left, key);
}

// Function to delete the entire tree (post-order traversal)
void deleteTree(struct Node* node) {
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

// Function to print the tree in-order
void inOrder(struct Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Main function to test the AVL tree implementation
int main() {
    struct Node *root = NULL;

    printf("Creating and inserting items into AVL tree...\n");
    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("In-order traversal of the constructed AVL tree is:\n");
    inOrder(root);
    printf("\n");

    printf("\nSearching for item 30: ");
    if (searchItem(root, 30)) {
        printf("Found.\n");
    } else {
        printf("Not Found.\n");
    }

    printf("Searching for item 99: ");
    if (searchItem(root, 99)) {
        printf("Found.\n");
    } else {
        printf("Not Found.\n");
    }

    printf("\nDeleting item 30...\n");
    root = deleteItem(root, 30);
    printf("In-order traversal after deletion:\n");
    inOrder(root);
    printf("\n");

    printf("\nDeleting the entire tree...\n");
    deleteTree(root);
    root = NULL;
    printf("Tree deleted.\n");

    return 0;
}