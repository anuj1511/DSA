#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool detectCycleHelper(vector<vector<int>> adj, int src, vector<bool>& vis) {
    // first curr, second parent
    queue<pair<int, int>> q;
    q.push(make_pair(src, -1));
    vis[src] = true;

    while (q.empty() == false) {
        int curr = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int it : adj[curr]) {
            if (vis[it] == false) {
                q.push(make_pair(it, curr));
                vis[it] = true;
            } else if (it != parent) {
                return true;
            }
        }
    }
    return false;
}

bool detectCycle(vector<vector<int>> adj, int v) {
    vector<bool> vis(v + 1, false);
    for (int i = 1; i <= v; i++) {
        if (vis[i] == false) {
            if (detectCycleHelper(adj, i, vis)) {
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