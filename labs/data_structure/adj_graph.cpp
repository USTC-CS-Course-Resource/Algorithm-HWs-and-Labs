// A note here: when using priority_queue, even you are using a pointer, and you changed something, the order won't be maiantained!!!
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>
#include <set>
#include <assert.h>

using namespace std;

class Edge {
public:
    int i, j, w;
    Edge() {}
    Edge(int i, int j, int w):
        i(i), j(j), w(w) {}
};

class Node {
public:
    int id;
    int d;
    vector<Edge> adj;

    Node() {};
};

class AdjGraph {
public:
    Node* nodes;
    int n;
    AdjGraph(int n, int s): n(n) {
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].id = i;
            nodes[i].d = INT16_MAX;
        }
        nodes[s].d = 0;
    }

    Node& operator[](int i) {
        return nodes[i];
    }
};

void dijkstra(AdjGraph& graph) {
    // set<Node*> s;

    auto cmp = [&graph](const int &x, const int &y)->bool{ return graph[x].d > graph[y].d; };
    priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
    
    for (int i = 0; i < graph.n; i++) {
        q.push(i);
    }

    while (!q.empty()) {
        int u = q.top();
        q.pop();
        // s.insert(u);
        for (auto edge: graph[graph[u].id].adj) {
            if (graph[u].d + edge.w < graph[edge.j].d) {
                graph[edge.j].d = graph[u].d + edge.w;
                q.push(edge.j);
            }
        }
    }
}