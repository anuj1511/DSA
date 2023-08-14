#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

bool detectCycleHelper(int src, vector<bool>& vis, vector<bool>& stack, vector<vector<int>> adj) {
    vis[src] = true;
    stack[src] = true;

    for (int it : adj[src]) {
        if (vis[it] == false) {
            if (detectCycleHelper(it, vis, stack, adj)) {
                return true;
            }
        } else if (stack[it] == true) {
            return true;
        }
    }
    stack[src] = false;
    return false;
}

bool detectCycle(vector<vector<int>> adj, int v) {
    vector<bool> vis(v + 1, false);
    vector<bool> stack(v + 1, false);

    for (int i = 1; i <= v; i++) {
        if (vis[i] == false) {
            if (detectCycleHelper(i, vis, stack, adj)) {
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
        // x --> y
        adj[x].push_back(y);
    }

    bool isCycle = detectCycle(adj, v);

    if (isCycle) {
        cout << "Cycle Detected!" << endl;
    } else {
        cout << "No Cycle Found" << endl;
    }

    return 0;
}