#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

void dfs(int node, int parent, int& timer, vector<int>& vis,
    vector<int>& tin, vector<int>& low, vector<vector<int>>& adj,
    vector<int>& isArticulationPoint) {

    vis[node] = true;
    tin[node] = low[node] = timer++;
    int child = 0;

    for (auto it : adj[node]) {
        if (it == parent) continue;

        if (!vis[it]) {
            dfs(it, node, timer, vis, tin, low, adj, isArticulationPoint);
            low[node] = min(low[node], low[it]);

            // Check AP
            // if there is no better way to reach then it is articulation point
            if (low[it] >= tin[node] && parent != -1) {
                isArticulationPoint[node] = true;
            }
            child++;
        } else {
            // backedge
            low[node] = min(low[node], low[it]);
        }
    }

    if (parent == -1 && child > 1) {
        isArticulationPoint[node] = true;
    }
}

void printArticulationPoint(vector<vector<int>>& adj, int nodes) {
    vector<int> vis(nodes, false);
    vector<int> tin(nodes, -1);
    vector<int> low(nodes, -1);
    vector<int> isArticulationPoint(nodes, false);

    int timer = 0;
    for (int i = 0; i < nodes; i++) {
        if (vis[i]) continue;
        dfs(i, -1, timer, vis, tin, low, adj, isArticulationPoint);
    }

    for (int i = 0; i < nodes; i++) {
        if (isArticulationPoint[i]) cout << i + 1 << " ";
    } cout << endl;
}

int main() {
    int nodes, edges; cin >> nodes >> edges;
    vector<vector<int>> adj(nodes);
    for (int i = 0; i < edges; i++) {
        int x, y; cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    printArticulationPoint(adj, nodes);

    return 0;
}

/*
12 14
1 2
2 3
3 4
1 4
4 5
5 6
6 7
7 8
8 9
6 9
8 10
10 11
11 12
12 10

Output:
4 5 6 8 10
 */