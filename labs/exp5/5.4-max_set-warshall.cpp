#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

bool** transitive_closure(bool** reachable, int n) {
    bool** next_reachable = new bool*[n];
    for (int i = 0; i < n; i++) {
        next_reachable[i] = new bool[n];
    }

    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            memset(next_reachable[l], 0, sizeof(bool) * n);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                next_reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
            }
        }
        swap(next_reachable, reachable);
    }

    for (int i = 0; i < n; i++) {
        delete[] next_reachable[i];
    }
    delete[] next_reachable;

    return reachable;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    bool** reachable = new bool*[n];
    for (int i = 0; i < n; i++) {
        reachable[i] = new bool[n];
        memset(reachable[i], 0, sizeof(bool) * n);
        reachable[i][i] = true;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        reachable[u-1][v-1] = true;
    }

    reachable = transitive_closure(reachable, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            reachable[i][j] = reachable[j][i] || reachable[i][j];
            // printf("%d\t", reachable[i][j]);
        }
        // cout << endl;
    }


}