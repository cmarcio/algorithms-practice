#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INCOLOR 'c'

void addVertex(vector< vector<int> > &g, int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

// codigo disponibilizado pelo professor
bool bipartite(vector<vector<int> > &graph,int u, int size) {
    queue<int> q;
    q.push(u);
    vector<int> color(size, INCOLOR);
    color[u] = 0;
    bool isBipartite = true;

    while (!q.empty()) {
        int k = q.front(); q.pop();
        for (int j = 0; j < graph[k].size(); j++) {
            int v = graph[k][j];
            if (color[v] == INCOLOR) {
                color[v] = 1 - color[k];
                q.push(v);
            } else if (color[v] == color[k]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, l, a, b;

    while (cin >> n && n != 0) {
        cin >> l;
        vector< vector<int> > graph(200);
        for (int i = 0; i < l; i++) {
            cin >> a >> b;
            addVertex(graph, a, b);
        }

        if (bipartite(graph, 0, n))
            cout << "BICOLORABLE.\n";
        else cout << "NOT BICOLORABLE.\n";
    }

    return 0;
}