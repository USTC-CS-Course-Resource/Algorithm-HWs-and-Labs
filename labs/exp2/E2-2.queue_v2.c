#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

const int HASH_SIZE = 2 << 20;

typedef struct Node {
    long name;
    int count;
    struct Node* next;
} Node;

Node* new_Node(long name) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->name = name;
    node->count = 0;
    node->next = NULL;
    return node;
}

#define INCREASE 0
#define INSERT 1
int hash_insert(Node** counter, long name) {
    Node* place = counter[name % HASH_SIZE];
    if (place == NULL) {
        counter[name % HASH_SIZE] = new_Node(name);
        return INSERT;
    }
    while(place->next) {
        if (place->name == name) {
            place->count++;
            return INCREASE;
        }
        place = place->next;
    }
    if (place->name == name) {
        place->count++;
        return INCREASE;
    }
    else {
        place->next = new_Node(name);
        return INSERT;
    }
}

#define DECREASE 0
#define REMOVE 1
#define UNFOUND -1
int hash_decrease(Node** counter, long name) {
    Node* place = counter[name % HASH_SIZE];
    Node* front = NULL;
    while (place && place->name != name) {
        front = place;
        place = place->next;
    }
    if (place == NULL) return UNFOUND;
    if (place->count == 1) {
        if (front == NULL) {
            counter[name % HASH_SIZE] = NULL;
        }
        else {
            front->next = place->next;
        }
        free(place);
        return REMOVE;
    }
    else {
        place->count--;
    }
    return DECREASE;
}

Node* hash_find(Node** counter, long name) {
    Node* place = counter[name % HASH_SIZE];
    while (place && place->name != name) {
        place = place->next;
    }
    return place;
}

void print_names(char** names, int i, int j) {
    printf("[from %d to %d] ", i, j);
    for (int k = i; k <= j; k++) {
        printf("%s ", names[k]);
    }
    printf("\n");
}

void print_longnames(long* names, int i, int j) {
    printf("[from %d to %d] ", i, j);
    for (int k = i; k <= j; k++) {
        printf("%ld ", names[k]);
    }
    printf("\n");
}

int isIn(long* names, int i, int j, long name) {
    for (int k = i; k <=j; k++) {
        //printf("%s %s %d\n", names[k], name, strcmp(names[k], name));
        if (names[k] == name) {
            return true;
        }
    }
    return false;
}

long name_to_long(char* name) {
    long v = 0;
    memcpy((char*)&v, name, sizeof(long));
    return v;
}

int main() {
    int n, k;
    char name[8];
    scanf("%d%d", &n, &k);
    long* names = (long*)malloc(n * sizeof(long));
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        names[i] = name_to_long(name);
    }

    Node** counter = (Node**)malloc(sizeof(Node*) * HASH_SIZE);
    memset(counter, 0, sizeof(Node*)*HASH_SIZE);
    
    int i = 0;
    int j = -1;
    int q_count = 0;
    int rtn_code;
    int wnd_count = 0;

    while (i + k - 1 < n) {
        // 找到从 i 开始最小的能包含 k 个名字的范围 i 到 j
        while (wnd_count < k && j < n - 1) {
            j++;
            rtn_code = hash_insert(counter, names[j]);
            if (rtn_code == INSERT) wnd_count++;
        }
        q_count++;
        // print_longnames(names, i, j);
        // 尝试继续扩展
        while (wnd_count == k && j < n - 1) {
            j++;
            Node* rtn = hash_find(counter, names[j]);
            if (rtn != NULL) {
                rtn->count++;
                q_count++;
                // print_longnames(names, i, j);
            }
            else break;
        }
        // 把加入了的hash信息都清空
        for (; i <= j; j--) {
            hash_decrease(counter, names[j]);
        }
        // 考虑下一个起点
        i++;
        wnd_count = 0;
        j = i-1;
    }
    printf("%d\n", q_count);
}