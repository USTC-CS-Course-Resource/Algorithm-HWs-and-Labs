#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#include <vector>

using namespace std;

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

class Edge {
public:
    int i, j, cost;
    Edge() {}
    Edge(int i, int j, int cost):
        i(i), j(j), cost(cost) {}
};

int min_cost_kruskal(vector<Edge> edges, int n) {
    int min_cost = 0;
    DisjSet disjset(n);
    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) { return e1.cost < e2.cost; });

    for (auto&& edge: edges) {
        if (disjset.find_set(edge.i) != disjset.find_set(edge.j)) {
            disjset.union_set(edge.i, edge.j);
            min_cost += edge.cost;
        }
    }
    return min_cost;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);


    int** costs = new int*[n];
    for(int i = 0; i < n; i++) {
        costs[i] = new int[n];
        memset(costs[i], -1, sizeof(int) * n);
    }


    set<pair<int, int>> appeared_edges;    
    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int c1, c2, cost;
        scanf("%d %d %d", &c1, &c2, &cost);
        appeared_edges.insert(pair<int, int>(c1-1, c2-1));
        if (costs[c1-1][c2-1] == -1) costs[c1-1][c2-1] = cost;
        else costs[c1-1][c2-1] = min(cost, costs[c1-1][c2-1]); // use city index - 1
    }

    for (auto&& edge: appeared_edges) {
        edges.push_back(Edge(edge.first, edge.second, costs[edge.first][edge.second]));
    }

    printf("%d\n", min_cost_kruskal(edges, n));
}
