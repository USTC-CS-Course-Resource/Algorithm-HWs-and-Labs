#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1
#define true 1
#define false 0

typedef struct RBNode {
    int low;
    int high;
    int max;
    int color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* p;
} RBNode;

typedef struct RBTree {
    struct RBNode* nil;
    struct RBNode* root;
} RBTree;

void update_max(RBNode* x) {
    x->max = x->high > x->left->max ? x->high : x->left->max;
    x->max = x->max > x->right->max ? x->max : x->right->max;
}

int is_overlap(RBNode* x, RBNode* y) {
    return (!(x->low > y->high || x->high < y->low));
}

void RB_Init(RBTree* T) {
    T->nil = (RBNode*)malloc(sizeof(RBNode));
    T->nil->color = BLACK;
    T->nil->low = -1;
    T->nil->high = -1;
    T->nil->max = -1;
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
    update_max(x);
    update_max(y);
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
    update_max(x);
    update_max(y);
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
        if (z->low < x->low) x = x->left;
        else x = x->right;
    }
    z->p = y;
    if (y == T->nil) T->root = z;
    else if (z->low < y->low) y->left = z;
    else y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    x = z;
    while (x != T->nil) {
        update_max(x);
        x = x->p;
    }
    RB_Insert_Fixup(T, z);
}

RBNode* Interval_Search(RBTree* T, RBNode* i) {
    RBNode* x = T->root;
    while (x != T->nil && !is_overlap(i, x)) {
        if (x->left != T->nil && x->left->max >= i->low) x = x->left;
        else x = x->right;
    }
    return x;
}

int main() {
    RBTree* T = (RBTree*)malloc(sizeof(RBTree));
    RB_Init(T);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int low, high;
        scanf("%d%d", &low, &high);
        RBNode* x = (RBNode*)malloc(sizeof(RBNode));
        x->low = low;
        x->high = high;
        x->max = x->high;
        x->color = BLACK;
        x->left = x->right = x->p = NULL;
        if (Interval_Search(T, x) == T->nil) {
            RB_Insert(T, x);
            printf("0\n");
        }
        else {
            printf("-1\n");
        }
    }
}