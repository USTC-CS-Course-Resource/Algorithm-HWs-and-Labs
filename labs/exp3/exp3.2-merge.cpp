#include <iostream>
#include <climits>

using namespace std;

constexpr int MAX_N = 200;

int time_costs[MAX_N][MAX_N] = {0};
int sum_costs[MAX_N][MAX_N] = {0};
int lengths[MAX_N] = {0};

void min_merge_time(int* lengths, int i, int j) {
    if (i == j) return;
    int min_time = INT_MAX;
    for (int k = i; k < j; k++) {
        if (time_costs[i][k] == 0) min_merge_time(lengths, i, k);
        if (time_costs[k+1][j] == 0) min_merge_time(lengths, k+1, j);
        if (sum_costs[i][k] == 0) {
            for (int m = i; m <= k; m++) {
                sum_costs[i][k] += lengths[m];
            }
        }
        if (sum_costs[k+1][j] == 0) {
            for (int m = k+1; m <= j; m++) {
                sum_costs[k+1][j] += lengths[m];
            }
        }
        min_time = min(min_time, time_costs[i][k] + time_costs[k+1][j] + (sum_costs[i][k] + sum_costs[k+1][j]));
    }
    time_costs[i][j] = min_time;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", lengths + i);
    }

    min_merge_time(lengths, 0, n-1);

    printf("%d\n", time_costs[0][n-1]);
}