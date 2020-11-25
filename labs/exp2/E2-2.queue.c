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

int isIn(char** names, int i, int j, char* name) {
    for (int k = i; k <=j; k++) {
        //printf("%s %s %d\n", names[k], name, strcmp(names[k], name));
        if (strcmp(names[k], name) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    char** names = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        names[i] = (char*)malloc(sizeof(char)*6);
        scanf("%s", names[i]);
    }
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