// Shortest Path in Directed Acyclic Graph              

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

#define INF INT_MAX

void topoHelper(int src, vector<pair<int, int>> adj[], vector<bool>& vis, stack<int>& st) {
    vis[src] = true;
    for (pair<int, int > it : adj[src]) {
        int curr = it.first;
        if (vis[curr] == false) {
            topoHelper(curr, adj, vis, st);
        }
    }
    st.push(src);
}

stack<int> topoSort(vector<pair<int, int>> adj[], int nodes) {
    stack<int> st;
    vector<bool> vis(nodes, false);

    for (int i = 0; i < nodes; i++) {
        if (vis[i] == false) {
            topoHelper(i, adj, vis, st);
        }
    }

    return st;
}

vector<int> shortestPath(vector<pair<int, int>> adj[], int nodes, int src) {
    vector<int> dist(nodes, INF);
    dist[src] = 0;

    stack<int> st = topoSort(adj, nodes);

    while (st.empty() == false) {
        int curr = st.top();
        st.pop();
        if (dist[curr] != INF) {
            for (pair<int, int> it : adj[curr]) {
                if (dist[curr] + it.second < dist[it.first]) {
                    dist[it.first] = dist[curr] + it.second;
                }
            }
        }
    }

    return dist;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<pair<int, int>> adj[nodes];

    int x, y, weight;
    for (int i = 0; i < edges; i++) {
        cin >> x >> y >> weight;
        // x --> y
        adj[x].push_back(make_pair(y, weight));
    }

    vector<int> dist = shortestPath(adj, nodes, 0);

    for (int it : dist) {
        it == INF ? cout << "INF" << " " : cout << it << " ";
    } cout << endl;

    return 0;
}

/*
6 7
0 1 2
0 4 1
1 2 3
2 3 6
4 2 2
4 5 4
5 3 1
 */