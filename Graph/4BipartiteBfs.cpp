#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartiteHelper(int src, vector<int>& color, vector<vector<int>> adj) {
    queue<int> q;
    q.push(src);
    color[src] = 0;

    while (q.empty() == false) {
        int node = q.front();
        q.pop();

        for (int it : adj[node]) {
            if (color[it] == -1) {
                color[it] = 1 - color[node];
                q.push(it);
            } else if (color[it] == color[node]) {
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>> adj, int v) {
    vector<int> color(v + 1, -1);

    for (int i = 1; i <= v; i++) {
        if (color[i] == -1) {
            if (isBipartiteHelper(i, color, adj) == false) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int v; cin >> v;
    int edges; cin >> edges;

    vector<vector<int>> adj(v + 1);
    int x, y;

    for (int i = 0; i < edges; i++) {
        cin >> x >> y;
        // x <--> y
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    bool bipartite = isBipartite(adj, v);

    if (bipartite) {
        cout << "Graph is Bipartite!" << endl;
    } else {
        cout << "Graph is NOT Bipartite" << endl;
    }

    return 0;
}