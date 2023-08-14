#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

void dfs(int& timer, int node, int parent, vector<int>& vis, vector<int>& tin, vector<int>& low, vector<vector<int>>& adj) {
    vis[node] = true;
    tin[node] = low[node] = timer++;

    for (auto it : adj[node]) {
        if (it == parent) continue;

        if (vis[it] == false) {
            dfs(timer, it, node, vis, tin, low, adj);
            low[node] = min(low[node], low[it]);
            // there is no other path to react it other than through node
            if (low[it] > tin[node]) {
                cout << node << " " << it << endl;
            }
        } else {
            // back edge
            low[node] = min(low[node], low[it]);
        }
    }
}

void printBridges(vector<vector<int>>& adj, int nodes) {
    vector<int> vis(nodes, 0);
    vector<int> tin(nodes, 0);
    vector<int> low(nodes, 0);

    int timer = 0;
    for (int i = 0; i < nodes; i++) {
        if (vis[i]) continue;
        dfs(timer, i, -1, vis, tin, low, adj);
    }
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    vector<vector<int>> adj(nodes);
    for (int i = 0; i < edges; i++) {
        int x, y; cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    printBridges(adj, nodes);

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
7 9
4 5
3 4
 */