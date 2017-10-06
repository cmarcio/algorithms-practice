#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

vector<vector<pair<int,int> > > graph;
priority_queue<pair<int,int> > pq;
map<int, bool> taken;
map<int, bool> weight_removed;

void initialize(int n) {
    graph.clear();
    graph.resize(1000);
    //taken.assign(n, 0);
    taken.clear();
    weight_removed.clear();
}

void addEdge(int u, int v, int weight) {
    graph[u].push_back(make_pair(-weight, v));   // peso antes para priorizar o peso
    graph[v].push_back(make_pair(-weight, u));
}

void process(int u) {
    taken[u] = true;
    for (int i = 0; i < graph[u].size(); i++)
        pq.push(graph[u][i]);
}

bool has_unvisited() {
    for (map<int,bool>::iterator p = taken.begin(); p != taken.end(); p++) {
        if( !p->second )
            return true;
    }
    return false;
}

int unvisited() {
    for (map<int,bool>::iterator p = taken.begin(); p != taken.end(); p++) {
        if( !p->second )
            return p->first;
    }
}

// codigo disponibilizado pelo professor
int prim(int x) {
    process(x);

    int mst_cost = 0;

    while (!pq.empty()) {
        pair<int,int> front = pq.top(); pq.pop();
        int u = front.second;
        int w = -front.first;
        if (!taken[u]) {
            mst_cost += w;
            process(u);
            weight_removed[w] = true;
        }

        if (pq.empty() && has_unvisited()) {
            process(unvisited());
        }
    }
    return mst_cost;
}

int main() {
    int m, n;
    int u, v, weight;

    while (cin >> m >> n && m != 0) {
        bool forest = true;
        initialize(m);
        for (int i = 0; i < n; i++) {
            cin >> u >> v >> weight;
            addEdge(u, v, weight);
            weight_removed[weight] = false;
            taken[u] = false;
            taken[v] = false;
        }

        prim(u);
        bool first = true;
        for (map<int,bool>::iterator p = weight_removed.begin(); p != weight_removed.end(); p++) {
            if (!p->second) {
                if (first)
                    first = false;
                else cout << " ";
                cout << p->first;                
                forest = false;                
            }
        }

        if (forest)
            cout << "forest";

        cout << "\n";
    }

    return 0;
}