#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX

int getMinKey(vector<int> key, vector<bool> mstSet, int v) {
    int min = INT_MAX, minIndex;
    for (int i = 0; i < v; i++) {
        if (key[i] < min && mstSet[i] == false) {
            min = key[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void primsMst(vector<pair<int, int>> adj[], int v) {
    vector<int> key(v, INF);
    vector<bool> mstSet(v, false);
    vector<int> parent(v, -1);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < v - 1; count++) {
        int u = getMinKey(key, mstSet, v);
        mstSet[u] = true;

        for (pair<int, int> it : adj[u]) {
            int v = it.first;
            int weight = it.second;
            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = u, key[v] = weight;
            }
        }
    }

    cout << "MST: " << endl;
    for (int i = 1; i < v; i++) {
        cout << parent[i] << " " << i << " " << key[i] << endl;
    }
}

int main() {
    int v, e;
    cin >> v >> e;

    vector<pair<int, int>> adj[v];

    int x, y, weight;
    for (int i = 0; i < e; i++) {
        cin >> x >> y >> weight;
        adj[x].push_back(make_pair(y, weight));
        adj[y].push_back(make_pair(x, weight));
    }

    primsMst(adj, v);

    return 0;
}