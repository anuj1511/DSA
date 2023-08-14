/*

    1. Sort the edges as per the weights
    2. Choose the edge with smallest weight, and which doesn't
       make cycle
    3. Repeat step 2.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

class DSU {
    vector<int> parent;
    vector<int> rank;
    vector<int> size;

public:
    DSU(int n) {
        rank = vector<int>(n);
        parent = vector<int>(n);
        size = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }

    int findPar(int node) {
        if (parent[node] == node) return node;
        return parent[node] = findPar(parent[node]);
    }

    bool makeUnion(int u, int v) {
        u = findPar(u);
        v = findPar(v);

        if (u == v)
            return false;

        if (rank[u] < rank[v])
            swap(u, v);

        parent[v] = u;
        size[u] += size[v];

        if (rank[u] == rank[v])
            rank[u]++;

        return true;
    }

    bool sameSet(int u, int v) {
        u = findPar(u);
        v = findPar(v);

        if (u == v) return true;
        return false;
    }
};

class Node {
public:
    int u;
    int v;
    int wt;

    Node(int _u, int  _v, int _wt) {
        u = _u;
        v = _v;
        wt = _wt;
    }

    Node() {

    }
};

bool comp(Node n1, Node n2) {
    return n1.wt < n2.wt;
}

vector<Node> KruskalsMst(vector<Node> edges, int nodes) {
    sort(edges.begin(), edges.end(), comp);

    vector<Node> mst;
    DSU dsu(nodes);

    for (Node edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int wt = edge.wt;

        if (dsu.sameSet(u, v)) {
            continue;
        }

        dsu.makeUnion(u, v);
        mst.push_back(edge);
    }

    return mst;
}

/*
6
9
5 4 9
5 1 4
4 1 1
4 3 5
3 2 3
4 2 3
1 2 2
3 6 8
2 6 7
    4 -----  3
  / |\      |  \
5   |  \    |   6
  \ |    \  | /
    1 ----- 2
 */

int main() {
    int t; cin >> t;
    while (t--) {
        int nodes, noOfEdges; cin >> nodes >> noOfEdges;
        vector<Node> edges(noOfEdges);
        for (int i = 0; i < noOfEdges; i++) {
            int u, v, wt; cin >> u >> v >> wt;
            u--, v--;
            Node temp(u, v, wt);
            edges[i] = temp;
        }

        vector<Node> mst = KruskalsMst(edges, nodes);

        int cost = 0;
        for (auto edge : mst) {
            cost += edge.wt;
        }

        cout << cost << endl;
    }
    return 0;
}