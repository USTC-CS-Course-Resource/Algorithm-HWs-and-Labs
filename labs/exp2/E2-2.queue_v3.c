#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

const int HASH_SIZE = 32 * 32 * 32 * 32 * 32 ;

void print_longnames(long* names, int i, int j) {
    printf("[from %d to %d] ", i, j);
    for (int k = i; k <= j; k++) {
        printf("%ld ", names[k]);
    }
    printf("\n");
}

long name_to_long(char* name) {
    long v = 0;
    // memcpy((char*)&v, name, sizeof(long));
    int len = strlen(name);
    for (int i = len - 1; i >= 0; i--) {
        v += v * 32 + (name[i] - 'a');
    }
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

    int* counter = (int*)malloc(sizeof(int) * HASH_SIZE);
    memset(counter, 0, sizeof(int)*HASH_SIZE);
    
    int left = 0;
    int right_min = -1;
    int right_max = -1;
    int q_count = 0;
    int wnd_count = 0;

    // 不断考虑下一个 left
    while (left < n-k) {
        // 寻找 right_min
        while (wnd_count < k && right_min < n - 1) {
            right_min++;
            if (counter[names[right_min]] == 0) {
                wnd_count++;
            }
            counter[names[right_min]]++;
        }
        if (wnd_count != k) break;
        right_max = right_min;
        // print_longnames(names, left, right_min);

        // 尝试继续扩展, 寻找 right_max
        while (wnd_count == k && right_max < n - 1) {
            right_max++;
            if (counter[names[right_max]] == 0) {
                right_max--;
                break;
            }
            else {
                // print_longnames(names, left, right_max);
            }
        }

        q_count += right_max - right_min + 1;

        // 把之前left的计数减掉, 然后 left++
        if (counter[names[left]] == 1) wnd_count--;
        counter[names[left]]--;
        left++;
    }
    printf("%d\n", q_count);
}
