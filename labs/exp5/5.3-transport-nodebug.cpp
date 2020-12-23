#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>
#include <assert.h>

using namespace std;

class Edge {
public:
    int i, j, w, f;

    // used by residual network, so I didn't initialize them for all circumstances
    int idx;
    int reverse_idx;
    bool real;

    Edge() {}
    Edge(int i, int j, int w, int f, bool real):
        i(i), j(j), w(w), f(f), real(real), idx(0), reverse_idx(0) {}
    Edge(int i, int j, int w, int f, bool real, int idx, int reverse_idx):
        i(i), j(j), w(w), f(f), real(real), idx(idx), reverse_idx(reverse_idx) {}
};

using Path = vector<Edge>;

class Node {
public:
    int id;
    vector<Edge> adj;

    Node() {}
};

class AdjGraph {
public:
    vector<Node> nodes;

    AdjGraph(int n) {
        nodes.resize(n);
        for (int i = 0; i < n; i++) {
            nodes[i].id = i;
        }
    }

    Node& operator[](int i) {
        return nodes[i];
    }

    Edge* get_edge(int i, int j) {
        for (auto&& edge: nodes[i].adj) {
            if (edge.j == j) return &edge;
        }

        return nullptr;
    }

    AdjGraph split_parallel_edge() {
        AdjGraph new_graph(nodes.size() * nodes.size());
        int new_node_id = nodes.size();
        for (auto&& node: nodes) {
            for (auto&& edge: node.adj) {
                if (node.id <= edge.j) {
                    // we don't care edge that edge.i < edge.j
                    new_graph[node.id].adj.push_back(Edge(node.id, edge.j, edge.w, 0, true));
                }
                else if (get_edge(edge.j, node.id) != nullptr) {
                    // but if edge with edge.i > edge.j and Edge(edge.j, edge.i) exists, we need to split it.
                    new_graph[node.id].adj.push_back(Edge(node.id, new_node_id, edge.w, 0, true));
                    new_graph[new_node_id].adj.push_back(Edge(new_node_id, edge.j, edge.w, 0, true));
                    new_node_id++;
                }
                else {
                    new_graph[node.id].adj.push_back(Edge(node.id, edge.j, edge.w, 0, true));
                }
            }
        }
        new_graph.nodes.resize(new_node_id);
        return new_graph;
    }

    AdjGraph residual_network() {
        AdjGraph residual = AdjGraph(nodes.size());
        for (int i = 0; i < nodes.size(); i++) {
            residual[i].id = nodes[i].id;
            for (auto&& edge: nodes[i].adj) {
                int edgei_idx = residual[edge.i].adj.size();
                int edgej_idx = residual[edge.j].adj.size();
                residual[edge.i].adj.push_back(Edge(edge.i, edge.j, edge.w, edge.w-edge.f, true, edgei_idx, edgej_idx));
                residual[edge.j].adj.push_back(Edge(edge.j, edge.i, edge.w, edge.f, false, edgej_idx, edgei_idx));
            }
        }
        return residual;
    }

    inline void init_flow_to_zero() {
        for (auto&& node: nodes) {
            for (auto&& edge: node.adj) {
                edge.f = 0;
            }
        }
    }

    inline Edge& get_real_edge(const Edge& edge) {
        return nodes[edge.i].adj[edge.idx];
    }

    inline Edge& get_reverse_edge(const Edge& edge) {
        return nodes[edge.j].adj[edge.reverse_idx];
    }

    Path get_path_dfs(int s, int t) {
        // auto start = system_clock::now();
        Path path;
        bool visited[nodes.size()];
        memset(visited, 0, sizeof(bool) * nodes.size());
        get_path_dfs_sub(s, t, path, visited);
        return path;
    }

    bool get_path_dfs_sub(int i, int t, Path& path, bool* visited) {
        visited[i] = true;
        if (i == t) return true;
        for (auto&& edge: nodes[i].adj) {
            if (visited[edge.j] || edge.f <= 0) continue;
            path.push_back(edge);
            if (get_path_dfs_sub(edge.j, t, path, visited)) return true;
            path.pop_back();
        }
        return false;
    }

    int ford_fulkerson(int s, int t) {
        this->init_flow_to_zero();
        AdjGraph residual = residual_network();
        Path path = residual.get_path_dfs(s, t);

        while (!path.empty()) {
            int cf = SHRT_MAX;
            for (auto edge: path) {
                cf = min(cf, edge.f);
            }
            for (auto edge: path) {
                Edge& target_edge = residual.get_real_edge(edge);
                Edge& target_edge_reverse = residual.get_reverse_edge(edge);
                target_edge.f -= cf;
                target_edge_reverse.f += cf;
            }
            path = residual.get_path_dfs(s, t);
        }
        int max_flow = 0;
        for (auto edge: residual[s].adj) {
            if (edge.real) max_flow += residual.get_reverse_edge(edge).f;
        }
        return max_flow;
    }
};

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    s--; t--;

    AdjGraph graph(n);
 
    for (int i = 0; i < m; i++) {
        int n1, n2, life;
        scanf("%d %d %d", &n1, &n2, &life);
        // assert(life < SHRT_MAX); // the assert is true
        n1--; n2--;
        int adjsize = graph[n1].adj.size();
        Edge* edge = graph.get_edge(n1, n2);
        if (edge != nullptr) edge->w += life;
        else graph[n1].adj.push_back(Edge(n1, n2, life, 0, true));
    }

    // split reverse parallel edge, to fit the conditions of 2F algorithm
    graph = graph.split_parallel_edge();

    // and now we can finnaly run 2F algorithm
    printf("%d\n", graph.ford_fulkerson(s, t));
}
