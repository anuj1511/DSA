// Kahn's Algo:

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
    Topological sort:
    linear ordering of vertices such that
    if there is an edge u->v then u appears
    before v in that ordering.
 */

 /*
     Approach:
         Using Indegree
  */

vector<int> topoSort(vector<vector<int>> adj, int v) {
    vector<int> indegree(v + 1, 0);
    for (int i = 1; i <= v; i++) {
        for (int it : adj[i]) {
            indegree[it]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= v; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo;
    while (q.empty() == false) {
        int curr = q.front();
        q.pop();
        topo.push_back(curr);

        for (int it : adj[curr]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it);
            }
        }
    } cout << endl;
    return topo;
}

int main() {
    int v; cin >> v;
    int edges; cin >> edges;

    vector<vector<int>> adj(v + 1);
    int x, y;

    for (int i = 0; i < edges; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
    }

    vector<int> topo = topoSort(adj, v);
    for (int i : topo) {
        cout << i << " ";
    } cout << endl;

    return 0;
}

/*
    Input:
    6 6
    3 4
    4 2
    5 2
    5 1
    6 1
    6 3

    Output:
    5 6 1 3 4 2
 */