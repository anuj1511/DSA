#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dfsHelper(vector<vector<int>> adj, vector<bool>& vis, int curr) {
    cout << curr << " ";
    vis[curr] = true;
    for (int i : adj[curr]) {
        if (vis[i] == false) {
            dfsHelper(adj, vis, i);
        }
    }
}

void dfs(vector<vector<int>> adj) {
    int n = adj.size() - 1;
    vector<bool> vis(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (vis[i] == false) {
            dfsHelper(adj, vis, i);
        }
    } cout << endl;
}

void bfs(vector<vector<int>> adj) {
    int n = adj.size() - 1;
    vector<bool> vis(n + 1, false);

    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (vis[i] == false) {
            q.push(i);
            vis[i] = true;
            while (q.empty() == false) {
                int curr = q.front();
                cout << curr << " ";
                q.pop();

                for (int i : adj[curr]) {
                    if (vis[i] == false) {
                        vis[i] = true;
                        q.push(i);
                    }
                }
            } cout << endl;
        }
    }
}

void topologicalSort(vector<vector<int>> adj) {
    int n = adj.size() - 1;
    vector<int> indegree(n + 1, 0);

    for (vector<int> v : adj) {
        for (int j : v) {
            indegree[j]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        cout << node << " ";
        q.pop();
        for (int i : adj[node]) {
            indegree[i]--;
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
    } cout << endl;
}

int get_component(vector<vector<int>> adj, int src, vector<bool>& vis) {
    vis[src] = true;
    int size = 1;
    for (int i : adj[src]) {
        if (vis[i] == false) {
            size += get_component(adj, i, vis);
        }
    }
    return size;
}

vector<int> countComponents(vector<vector<int>> adj) {
    int n = adj.size() - 1;
    vector<int> ans;
    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (visited[i] == false) {
            ans.push_back(get_component(adj, i, visited));
        }
    }

    return ans;
}

int main() {
    int n, m;
    cout << "Enter no. of nodes: ";
    cin >> n;
    cout << "Enter no. of edges: ";
    cin >> m;

    vector<vector<int>> adj(n + 1);

    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    bfs(adj);
    topologicalSort(adj);

    return 0;
}
