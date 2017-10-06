#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int,int> > > graph;
priority_queue<pair<int,int> > pq;
vector<int> taken;

void initialize(int n) {
    graph.clear();
    graph.resize(n);
    taken.assign(n, 0);
}

void addEdge(int u, int v, int weight) {
    graph[u].push_back(make_pair(-weight, v));   // peso antes para priorizar o peso
    graph[v].push_back(make_pair(-weight, u));
}

void process(int u) {
    taken[u] = 1;
    for (int i = 0; i < graph[u].size(); i++)
        pq.push(graph[u][i]);
}

// codigo disponibilizado pelo professor
int prim() {
    process(0);

    int mst_cost = 0;

    while (!pq.empty()) {
        pair<int,int> front = pq.top(); pq.pop();
        int u = front.second;
        int w = -front.first;
        if (!taken[u]) {
            mst_cost += w;
            process(u);
        }
    }
    return mst_cost;
}

int main() {
    int m, n;
    int u, v, weight, total_weight;

    while (cin >> m >> n && m != 0) {
        initialize(m);
        total_weight = 0;
        for (int i = 0; i < n; i++) {
            cin >> u >> v >> weight;
            total_weight += weight;
            addEdge(u, v, weight);
        }
        cout << total_weight - prim() << "\n";
    }

    return 0;
}