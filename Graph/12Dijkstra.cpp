#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

#define INF INT_MAX

vector<int> dijkstra(vector<pair<int, int>> adj[], int v, int src) {
    vector<int> dist(v, INF);
    dist[src] = 0;
    priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));

    while (pq.empty() == false) {
        pair<int, int> curr = pq.top();
        pq.pop();

        int parent = curr.second;
        int parentDist = curr.first;
        for (pair<int, int> it : adj[parent]) {
            int child = it.first;
            int prentChidDist = it.second;
            if (dist[child] > parentDist + prentChidDist) {
                dist[child] = parentDist + prentChidDist;
                pq.push(make_pair(dist[child], child));
            }
        }
    }
    return dist;
}

int main() {

    int v, e; cin >> v >> e;
    vector<pair<int, int>> adj[v];

    int x, y, weight;
    for (int i = 0; i < e; i++) {
        cin >> x >> y >> weight;
        adj[x].push_back(make_pair(y, weight));
        adj[y].push_back(make_pair(x, weight));
    }

    vector<int> dist = dijkstra(adj, v, 0);

    for (int it : dist) {
        cout << it << " ";
    } cout << endl;

    return 0;
}