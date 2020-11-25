#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

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
    //print_longnames(names,0,n-1);
    int i = 0;
    int j = 0;
    int q_count = 0;
    while (i + k - 1 < n) {
        // 找到从 i 开始最小的能包含 k 个名字的范围 i 到 j
        int wnd_count = 1;
        while (wnd_count < k && j < n - 1) {
            j++;
            if (!isIn(names, i, j-1, names[j])) {
                wnd_count++;
            }
        }
        q_count++;
        // 尝试继续扩展
        while (wnd_count == k && j < n - 1) {
            j++;
            if (isIn(names, i, j-1, names[j])) {
                q_count++;
            }
            else break;
        }
        i++;
        j = i;
    }
    printf("%d\n", q_count);
}