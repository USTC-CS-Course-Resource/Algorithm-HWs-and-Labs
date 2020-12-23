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
};

void dijkstra(AdjGraph& graph) {
    // set<Node*> s;

    auto cmp = [](const Node *x, const Node *y)->bool{ return x->d > y->d; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> q(cmp);
    
    for (int i = 0; i < graph.n; i++) {
        q.push(&graph.nodes[i]);
    }

    while (!q.empty()) {
        Node* u = q.top();
        q.pop();
        // s.insert(u);
        for (auto edge: graph.nodes[u->id].adj) {
            if (u->d + edge.w < graph.nodes[edge.j].d) {
                graph.nodes[edge.j].d = u->d + edge.w;
                q.push(&graph.nodes[edge.j]);
            }
        }
    }
}