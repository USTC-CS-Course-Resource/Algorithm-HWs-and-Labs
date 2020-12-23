#include <iostream>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

class Node {
public:
    int id;
    vector<int> adj;

    // for node
    bool instack;
    int dfn;
    int low;
    int belong;
    
    // for super-node
    int size;
    int max_depth;

    Node(): instack(false), dfn(0), low(0), belong(-1), size(0), max_depth(0) {};
};

class AdjGraph {
public:
    Node* nodes;
    int n;
    AdjGraph(int n): n(n) {
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].id = i;
        }
    }

    Node& operator[](int i) {
        return nodes[i];
    }
};

constexpr int SIZE = 8192;

// ![Tarjan算法](https://byvoid.com/zhs/blog/scc-tarjan/)
int visit_index = 0;
int bcnt = 0;
stack<int> visit_stack;
void tarjan_sub(AdjGraph& graph, int i) {
    graph[i].dfn = graph[i].low = ++visit_index; // visit node i
    graph[i].instack = true;
    visit_stack.push(i);
    for (auto j: graph[i].adj) {
        // traverse all nodes[i]'s adjacent nodes, which is a DFS
        if (!graph[j].dfn) {
            // nodes[j] wasn't visited
            tarjan_sub(graph, j);
            // and nodes[j] might reach lower
            graph[i].low = min(graph[i].low, graph[j].low);
        }
        else if (graph[j].instack) {
            // nodes[j] is in stack and was visited, then it might be nodes[i]'s ancestor, which has lower visit_index
            graph[i].low = min(graph[i].low, graph[j].dfn);
        }
    }

    if (graph[i].dfn == graph[i].low) {
        // indicating a strongly connected component, just pop them out and mark them
        int j;
        do {
            j = visit_stack.top(); visit_stack.pop();
            graph[j].instack = false;
            graph[j].belong = bcnt;
        } while (j != i);
        bcnt++;

    }
}

int tarjan(AdjGraph& graph) {
    visit_index = 0;
    bcnt = 0;
    while (!visit_stack.empty()) visit_stack.pop();

    for (int i = 0; i < graph.n; i++) {
        if (!graph[i].dfn) tarjan_sub(graph, i);
    }

    return bcnt;
}

int max_depth = 0;
void dfs_sub(AdjGraph& graph, int i) {
#ifdef DEBUG
    printf("visit %d\n", i);
#endif
    if (graph[i].adj.empty()) {
        graph[i].max_depth = graph[i].size;
        return;
    }
    int max_child_depth = 0;
    for (auto child: graph[i].adj) {
        dfs_sub(graph, child);
        max_child_depth = max(graph[child].max_depth, max_child_depth);
    }
    graph[i].max_depth = max_child_depth + graph[i].size;
}

void dfs(AdjGraph& graph) {
    max_depth = 0;
    for (int i = 0; i < graph.n; i++) {
        if (graph[i].max_depth == 0) dfs_sub(graph, i);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    AdjGraph graph(n);

    for (int i = 0; i < m; i++) {
        int c1, c2;
        scanf("%d %d", &c1, &c2);
        c1--; c2--;
        int adjsize = graph[c1].adj.size();
        int j = 0;
        for (j = 0; j < adjsize; j++) {
            if (graph[c1].adj[j] == c2) break;
        }
        if (j == adjsize) graph[c1].adj.push_back(c2);
    }

    // invoking this, we set all nodes with a `belong`, indicating its strongly connected component
    int scc_cnt = tarjan(graph);

#ifdef DEBUG
    for (int i = 0; i < graph.n; i++) {
        printf("node %d's adj: ", i);
        for (auto j: graph[i].adj) {
            printf("%d ", j);
        }
        printf("\n");
    }
    for (int i = 0; i < graph.n; i++) {
        printf("node %d is in %d\n", i, graph[i].belong);
    }
#endif

    // now we can consider each strongly connected component as a super-node
    AdjGraph super_graph(scc_cnt);
    for (int i = 0; i < graph.n; i++) {
        super_graph[graph[i].belong].size++;
        for (auto j: graph[i].adj) {
            if (graph[j].belong == graph[i].belong) continue;
            int adjsize = super_graph[graph[i].belong].adj.size();
            int k = 0;
            for (k = 0; k < adjsize; k++) {
                if (super_graph[graph[i].belong].adj[k] == graph[j].belong) break;
            }
            if (k == adjsize) {
                super_graph[graph[i].belong].adj.push_back(graph[j].belong);
            }
        }
    }

#ifdef DEBUG
    for (int i = 0; i < super_graph.n; i++) {
        printf("super-node %d's adj: ", i);
        for (auto j: super_graph[i].adj) {
            printf("%d ", j);
        }
        printf("\n");
    }
#endif

    // and then do DFS to find the "deepest" path(deepest here means the sum of the node sizes)
    dfs(super_graph);

    max_depth = 0;
    for (int i = 0; i < super_graph.n; i++) {
#ifdef DEBUG
        printf("node %d's max depth: %d\n", i, super_graph[i].max_depth);
#endif
        max_depth = max(super_graph[i].max_depth, max_depth);
    }

    printf("%d\n", max_depth);
}