#include <iostream>
#include <vector>
using namespace std;

bool detectCycleHelper(vector<vector<int>> adj, int src, int parent, vector<bool>& vis) {
    vis[src] = true;

    for (int i : adj[src]) {
        if (vis[i] == false) {
            if (detectCycleHelper(adj, i, src, vis)) {
                return true;
            }
        } else if (i != parent) {
            return true;
        }
    }

    return false;
}

bool detectCycle(vector<vector<int>> adj, int v) {
    vector<bool> vis(v + 1, false);
    for (int i = 1; i <= v; i++) {
        if (vis[i] == false) {
            if (detectCycleHelper(adj, i, -1, vis)) {
                return true;
            }
        }
    }
    return false;
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

    bool isCycle = detectCycle(adj, v);

    if (isCycle) {
        cout << "Cycle Detected!" << endl;
    } else {
        cout << "No Cycle Found" << endl;
    }

    return 0;
}