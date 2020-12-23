#include <iostream>

class DisjSetNode {
public:
    size_t p;
    size_t rank;
    DisjSetNode() {}
};


class DisjSet {
private:
    DisjSetNode* disjset;
    void link(size_t x, size_t y) {
        if (disjset[x].rank > disjset[y].rank) disjset[y].p = x;
        else {
            disjset[x].p = y;
            if (disjset[x].rank == disjset[y].rank) {
                disjset[y].rank++;
            }
        }
    }

public:

    DisjSet(size_t n) {
        disjset = new DisjSetNode[n];
        for (int i = 0; i < n; i++) {
            disjset[i].p = i;
            disjset[i].rank = 0;
        }
    }

    void union_set(size_t x, size_t y) {
        link(find_set(x), find_set(y));
    }

    size_t find_set(size_t x) {
        if (x != disjset[x].p) disjset[x].p = find_set(disjset[x].p);
        return disjset[x].p;
    }
};
