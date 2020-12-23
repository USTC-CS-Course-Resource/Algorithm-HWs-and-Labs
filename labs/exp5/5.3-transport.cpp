#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>
#include <set>
#include <assert.h>

using namespace std;

class Node {
public:
    int id;
    int d;
    vector<int> adj;

    Node() {};
};

class MatGraph {
public:
    Node* nodes;
    int n;
    int** c;
    int** cf;

    MatGraph(int n): n(n) {
        c = new int*[n];
        cf = new int*[n];
        for (int i = 0; i < n; i++) {
            c[i] = new int[n]; memset(c[i], -1, sizeof(int) * n);
            cf[i] = new int[n]; memset(cf[i], -1, sizeof(int) * n);
        }
    }
};


int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    s--; t--;

    MatGraph graph(n);
    set<pair<int,int>> tester;

    for (int i = 0; i < m; i++) {
        int n1, n2, life;
        scanf("%d %d %d", &n1, &n2, &life);
        n1--; n2--;
        
        assert(tester.find(pair<int,int>(n1,n2)) == tester.end());
        tester.insert(pair<int,int>(n1, n2));
        // graph.c[n1][n2] += life;
        // graph.cf[n1][n2] = 0;
        // graph.nodes[n1].adj.push_back(n2);
    }

    printf("just test you hhhh");
}