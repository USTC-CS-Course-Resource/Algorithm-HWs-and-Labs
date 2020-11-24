#include <stdio.h>
#include <stdlib.h>

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

void bst_update_size(Node* x) {
    x->size = 1;
    if (x->left) x->size += x->left->size;
    if (x->right) x->size += x->right->size;
}

Node* bst_search(Node* x, int k) {
    if (!x || k == x->key) return x;
    if (k < x->key) return bst_search(x->left, k);
    else return bst_search(x->right, k);
}

void bst_insert(Tree* T, Node* z) {
    Node* y = NULL;
    Node* x = T->root;
    while (x) { // y is x.p
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->p = y;
    if (!y)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    // update size from z->p
    Node* zp = z->p;
    while(zp != NULL) {
        bst_update_size(zp);
        zp = zp->p;
    }
}

void bst_transplant(Tree* T, Node* u, Node* v) {
    // u为根
    if (!u->p) T->root = v;
    // u为左孩子
    else if (u == u->p->left) u->p->left = v;
    // u为右孩子
    else u->p->right = v;
    // v不为NULL
    if (v) v->p = u->p;
}

Node* bst_min(Node* x) {
    while (x->left) {
        x = x->left;
    }
    return x;
}

void bst_delete(Tree* T, Node* z) {
    // z左子树为空
    if (!z->left) {
        Node* x = z->p;
        bst_transplant(T, z, z->right);
        while(x != NULL) {
            bst_update_size(x);
            x = x->p;
        }
    }
    // z右子树为空
    else if (!z->right) {
        Node* x = z->p;
        bst_transplant(T, z, z->left);
        while(x != NULL) {
            bst_update_size(x);
            x = x->p;
        }
    }
    // z有两个孩子
    else {
        Node* y = bst_min(z->right);
        Node* x = y;
        if (y->p != z) {
            x = y->p;
            bst_transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        bst_transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        // update size
        while(x != NULL) {
            bst_update_size(x);
            x = x->p;
        }
    }
    free(z);
}

Node* bst_search_kthmin(Node* root, int rank) {
    int lsize = root->left ? root->left->size : 0;
    int rsize = root->right ? root->right->size : 0;
    // if (rank > root->size) {
    //     printf("-----------------------------------------------------------error!\n");
    //     printf("搜 %d rank(%d) lsize(%d) left(%ld, %d) right(%ld, %d) rootsize(%d)\n", root->key, rank, lsize, root->left, lsize, root->right, rsize, root->size);
    //     return root;
    // }
    //printf("搜 %d rank(%d) lsize(%d) left(%ld, %d) right(%ld, %d)\n", root->key, rank, lsize, root->left, lsize, root->right, rsize);
    if (lsize < rank - 1) {
        return bst_search_kthmin(root->right, rank - lsize - 1);
    }
    else if (lsize == rank - 1) {
        return root;
    }
    else {
        return bst_search_kthmin(root->left, rank);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Tree* T = (Tree*)malloc(sizeof(Tree));
    T->root = NULL;

    char op[1];
    int value;
    Node* x;
    int I = 0;
    int D = 0;
    for (int i = 0; i < n; i++) {
        int rsize = T->root ? T->root->size:0;
        if (I-D != rsize) {
            printf("D: %d, I: %d, size: %d, rootsize: %d   at line %d\n", D, I, I-D, rsize, i+2);
            break;
        }
        scanf("%s %d", op, &value);
        if (op[0] == 'I') {
            x = (Node*)malloc(sizeof(Node));
            x->left = NULL;
            x->right = NULL;
            x->p = NULL;
            x->key = value;
            x->size = 1;
            bst_insert(T, x);
            I++;
        }
        else if (op[0] == 'D') {
            x = bst_search(T->root, value);
            bst_delete(T, x);
            D++;
        }
        else if (op[0] == 'K') {
            x = bst_search_kthmin(T->root, value);
            printf("%d\n", x->key);
        }
    }
}