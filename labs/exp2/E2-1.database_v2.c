#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1
#define true 1
#define false 0

typedef struct RBNode {
    int key;
    int color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* p;
} RBNode;

typedef struct RBTree {
    struct RBNode* nil;
    struct RBNode* root;
} RBTree;

void RB_Init(RBTree* T) {
    T->nil = (RBNode*)malloc(sizeof(RBNode));
    T->nil->color = BLACK;
    T->nil->key = 0;
    T->nil->left = T->nil->right = T->nil->p = NULL;
    T->root = T->nil;
}

void RB_Left_Rotate(RBTree* T, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) y->left->p = x;
    y->p = x->p;
    if (x->p == T->nil) T->root = y;
    else if (x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->left = x;
    x->p = y;
}

void RB_Right_Rotate(RBTree* T, RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != T->nil) y->right->p = x;
    y->p = x->p;
    if (x->p == T->nil) T->root = y;
    else if (x == x->p->right) x->p->right = y;
    else x->p->left = y;
    y->right = x;
    x->p = y;
}

void RB_Insert_Fixup(RBTree* T, RBNode* z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            RBNode* y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) {
                    z = z->p;
                    RB_Left_Rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RB_Right_Rotate(T, z->p->p);
            }
        }
        else {
            RBNode* y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->left) {
                    z = z->p;
                    RB_Right_Rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RB_Left_Rotate(T, z->p->p);
            }
        }
        T->nil->color = BLACK;
    }
    T->root->color = BLACK;
}

void RB_Insert(RBTree* T, RBNode* z) {
    RBNode* y = T->nil;
    RBNode* x = T->root;
    while (x != T->nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->p = y;
    if (y == T->nil) T->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    RB_Insert_Fixup(T, z);
}

int RB_Search(RBTree* T, int key) {
    RBNode* x = T->root;
    while (true) {
        if (x->key == key) {
            return key;
        }
        else if (x->key < key) {
            if (x->right != T->nil) x = x->right;
            else {
                return x->key;
            }
        }
        else if (key < x->key) {
            if (x->left != T->nil) x = x->left;
            else {
                RBNode* y = x->p;
                while (x == y->left) {
                    x = y;
                    y = y->p;
                }
                return y->key;
            }
        }

    }
}

int main() {
    RBTree* T = (RBTree*)malloc(sizeof(RBTree));
    RB_Init(T);
    char op[32];
    int key;
    while (true) {
        scanf("%s", op);
        if (op[0] == 'I') {
            scanf("%d", &key);
            RBNode* x = (RBNode*)malloc(sizeof(RBNode));
            x->key = key;
            x->color = BLACK;
            x->left = x->right = x->p = NULL;
            RB_Insert(T, x);
        }
        else if (op[0] == 'F') {
            scanf("%d", &key);
            printf("%d\n", RB_Search(T, key));
        }
        else {
            break;
        }
    }
}