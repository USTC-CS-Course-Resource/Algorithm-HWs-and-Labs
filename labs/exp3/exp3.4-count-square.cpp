#include <iostream>

using namespace std;

int main() {
    int n, m;
    int count = 0;

    scanf("%d %d", &n, &m);

    uint8_t status[n][m];
    int max_count[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%hhd", &status[i][j]);
            max_count[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (status[i][j] == 1) {
                max_count[i][j] = 0;
                continue;
            }
            int max_size = 0;
            if (i > 0) max_size = max_count[i-1][j] - 1;
            if (j > 0) max_size = max(max_count[i][j-1] - 1, max_size);
            max_size = max(max_size, 0);
            // printf("%d\n", max_size);
            bool ok = true;
            for ( ;ok && i + max_size < n && j + max_size < m; max_size++) {
                for (int h = 0; h <= max_size; h++) {
                    if (status[i+max_size][j+h] == 1 || status[i+h][j+max_size] == 1) {
                        ok = false;
                        max_size--;
                        break;
                    }
                }
            }
            max_count[i][j] = max_size;
            count += max_count[i][j];
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("%2d ", max_count[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("%d\n", count);
}