#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
    Topological sort:
    linear ordering of vertices such that
    if there is an edge u->v then u appears
    before v in that ordering.
 */

 /*
     Approach:
         Using Dfs
         First insert the child then parent
         u->v
         first insert v is stack, then u

         then while printing stack we get, u v
  */

void topoHelper(int src, vector<bool>& vis, stack<int>& st, vector<vector<int>> adj) {
    vis[src] = true;
    for (int it : adj[src]) {
        if (vis[it] == false) {
            topoHelper(it, vis, st, adj);
        }
    }
    st.push(src);
}

vector<int> topoSort(vector<vector<int>> adj, int v) {
    stack<int> st;
    vector<bool> vis(v + 1, false);

    for (int i = 1; i <= v; i++) {
        if (vis[i] == false) {
            topoHelper(i, vis, st, adj);
        }
    }
    vector<int> topo;
    while (st.empty() == false) {
        topo.push_back(st.top());
        st.pop();
    }
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
    6 5 3 4 2 1
 */