#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        rank = vector<int>(n);
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findPar(int node) {
        if (parent[node] == node) return node;
        return parent[node] = findPar(parent[node]);
    }

    void makeUnion(int u, int v) {
        u = findPar(u);
        v = findPar(v);

        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            rank[u]++;
            parent[v] = u;
        }
    }

    bool sameSet(int u, int v) {
        u = findPar(u);
        v = findPar(v);

        if (u == v) return true;
        return false;
    }
};

int main() {

    return 0;
}