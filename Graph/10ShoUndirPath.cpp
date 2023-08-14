// Shortest Path in Undirected Graph with Unit Weights

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<int> findUnitDistance(vector<vector<int>> adj, int nodes, int src) {
    vector<int> dist(nodes, INT_MAX);
    dist[src] = 0;
    queue<int> q;
    q.push(src);

    while (q.empty() == false) {
        int curr = q.front();
        q.pop();
        for (int it : adj[curr]) {
            if (dist[it] > dist[curr] + 1) {
                dist[it] = dist[curr] + 1;
                q.push(it);
            }
        }
    }

    return dist;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<vector<int>> adj(nodes);

    int x, y;
    for (int i = 0; i < edges; i++) {
        cin >> x >> y;
        // x <--> y
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> dist = findUnitDistance(adj, nodes, 0);

    for (int it : dist) {
        cout << it << " ";
    } cout << endl;

    return 0;
}

/*
9 11
0 1
0 3
1 2
1 3
2 6
3 4
4 5
5 6
6 7
7 8
6 8

Output: 0 1 2 1 2 3 3 4 4
 */