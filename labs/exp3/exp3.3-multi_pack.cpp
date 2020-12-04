#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int n, W;
    scanf("%d %d", &n, &W);
    int max_value[n][W + 1]; // max_value[i][j] 表示考虑了前 i 个(从0开始), 对于容量为 j 的背包的最高价值
    
    memset(max_value, 0, sizeof(max_value));

    int weights[n];
    int values[n];
    int nums[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", weights + i, values + i, nums + i);
    }

    for (int j = 0; j <= W; j++) {
        for (int k = 0; k <= nums[0] && k * weights[0] <= j; k++) {
            max_value[0][j] = max(max_value[0][j],  k * values[0]);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= W; j++) {
            for (int k = 0; k <= nums[i] && k * weights[i] <= j; k++) {
                max_value[i][j] = max(max_value[i][j], max_value[i-1][j - k * weights[i]] + k * values[i]);
            }
        }
    }

    printf("%d\n", max_value[n-1][W]);
}
