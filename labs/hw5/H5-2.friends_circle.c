#include <stdio.h>
#include <stdlib.h>

int* disjset;

int find_root(int id) {
    if (disjset[id] != id) disjset[id] = find_root(disjset[id]);
    return disjset[id];
}

int union_set(int id1, int id2) {
    disjset[id1] = id2;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &k, &m);

    disjset = (int*)malloc(n*sizeof(int)+1);
    for (int i = 0; i < n; i++) {
        disjset[i] = i;
    }
    
    int p1, p2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &p1, &p2);
        union_set(find_root(p1), find_root(p2));
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &p1, &p2);
        if (find_root(p1) == find_root(p2)) printf("1 ");
        else printf("0 ");
    }
}
