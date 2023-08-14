#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartiteHelper(int src, vector<vector<int>> adj, vector<int>& color) {
    for (int it : adj[src]) {
        if (color[it] == -1) {
            color[it] = 1 - color[src];
            if (isBipartiteHelper(it, adj, color) == false) {
                return false;
            }
        } else if (color[it] == color[src]) {
            return false;
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>> adj, int v) {
    vector<int> color(v + 1, -1);
    for (int i = 1; i <= v; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            if (isBipartiteHelper(i, adj, color) == false) {
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