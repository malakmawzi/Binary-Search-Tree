#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* addNode(Node* root, int value);
Node* removeNode(Node* root, int value);
void displaySubtree(Node* N);
int numberLeaves(Node* N);
Node* removeSubtree(Node* root, int value);
int nodeDepth(Node* root, Node* N);

int main() {
    Node* root = NULL;
    root = addNode(root, 10);
    root = addNode(root, 5);
    root = addNode(root, 15);
    root = addNode(root, 2);
    root = addNode(root, 7);
    root = addNode(root, 12);
    root = addNode(root, 20);

    printf("Inorder traversal of the binary search tree:\n");
    displaySubtree(root);
    printf("\n");

    printf("Number of leaves in the binary search tree: %d\n", numberLeaves(root));

    Node* removed = removeNode(root, 5);
    printf("Inorder traversal of the binary search tree after removing node with value 5:\n");
    displaySubtree(root);
    printf("\n");

    printf("Depth of node with value 12 in the binary search tree: %d\n", nodeDepth(root, removed));

    root = removeSubtree(root, 15);
    printf("Inorder traversal of the binary search tree after removing subtree rooted at node with value 15:\n");
    displaySubtree(root);
    printf("\n");

    return 0;
}

Node* addNode(Node* root, int value) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (value < root->value) {
        root->left = addNode(root->left, value);
    }
    else if (value > root->value) {
        root->right = addNode(root->right, value);
    }

    return root;
}

Node* removeNode(Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if (value < root->value) {
        root->left = removeNode(root->left, value);
    }
    else if (value > root->value) {
        root->right = removeNode(root->right, value);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        else {
            Node* minNode = root->right;
            while (minNode->left != NULL) {
                minNode = minNode->left;
            }
            root->value = minNode->value;
            root->right = removeNode(root->right, minNode->value);
        }
    }

    return root;
}

void displaySubtree(Node* N) {
    if (N == NULL) {
        return;
    }

    displaySubtree(N->left);
    printf("%d ", N->value);
    displaySubtree(N->right);
}

int numberLeaves(Node* N) {
    if (N == NULL) {
        return 0;
    }

    if (N->left == NULL && N->right == NULL) {
        return 1;
    }

    return numberLeaves(N->left) + numberLeaves(N->right);
}

Node* removeSubtree(Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if (value < root->value) {
        root->left = removeSubtree(root->left, value);
    }
    else if (value > root->value) {
        root->right = removeSubtree(root->right, value);
    }
    else {
        if (root->left != NULL) {
            root->left = removeSubtree(root->left, root->left->value);
        }
        if (root->right != NULL) {
            root->right = removeSubtree(root->right, root->right->value);
        }
        free(root);
        return NULL;
    }

    return root;
}

int nodeDepth(Node* root, Node* N) {
    if (root == NULL) {
        return -1;
    }

    if (root == N) {
        return 0;
    }

    int leftDepth = nodeDepth(root->left, N);
    if (leftDepth >= 0) {
        return leftDepth + 1;
    }

    int rightDepth = nodeDepth(root->right, N);
    if (rightDepth >= 0) {
        return rightDepth + 1;
    }

    return -1;
}

