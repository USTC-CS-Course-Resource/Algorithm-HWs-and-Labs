#include <stdio.h>

typedef struct Node {
    struct Node* left;
    struct Node* right;
    struct Node* p;
    int key;
    int size;
} Node;

typedef struct Tree {
    Node* root;
} Tree;

void bst_insert(Node* root, Node* node) {
    if (node->key <= root->key) {
        if (!root->left) {
            root->left = node;
            node->p = root;
        }
        else bst_insert(root->left, node);
    }
    else {
        if (!root->right) {
            root->right = node;
            node->p = root;
        }
        else bst_insert(root->right, node);
    }
    root->size = 1;
    if (root->left) root->size += root->left->size;
    if (root->right) root->size += root->right->size;
}

Node* bst_min(Node* cur) {
    while (cur->left) {
        cur = cur->left;
    }
    return cur;
}

// Node* bst_succ(Node* x) {
//     if(x->right) return bst_min(x->right);
//     Node* y = x->p;
//     while (y && x == y.right) {
//         x = y;
//         y = y.p;
//     }
//     return y;
// }

void bst_transplant();

void bst_delete(Node* root, int key) {
    if (key < root->key) {
        bst_delete(root->left, key);
    }
    else if (key == root->key) {
        Node* succ = bst_succ(root);
        succ->p->left = succ->right;
    }
    else {
        bst_delete(root->right, key);
    }
    root->size = 1;
    if (root->left) root->size += root->left->size;
    if (root->right) root->size += root->right->size;
}

int main() {
    Node n5 = {NULL, NULL, NULL, 5, 1};
    Node n2 = {NULL, NULL, NULL, 2, 1};
    Node n8 = {NULL, NULL, NULL, 8, 1};
    bst_insert(&n5, &n2);
    bst_insert(&n5, &n8);
    printf("n5:  %d\n", n5.size);
    printf("n5l: %d %d\n", n5.left->key, n5.left->size);
    printf("n5r: %d %d\n", n5.right->key, n5.right->size);
    printf("2succ: %d\n", bst_succ(&n2)->key);
    printf("5succ: %d\n", bst_succ(&n5)->key);
    printf("8succ: %d\n", bst_succ(&n8)->key);

}