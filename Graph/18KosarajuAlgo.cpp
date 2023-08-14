/*
    Kosaraju Algo for strongly connected components

    Strongly connected components:
        These are the components in which we can reach to
        all the nodes of the component from any of the node.

    1 ----> 2 ------> 4 -------> 5
    ^\     /
      \  </
       3

    Strongly connected components-> [1,2,3],[4],[5]
 */

 /*
     Dry run on given example:

     first we will find the topo sort using stack

     stack: 3 5 4 2 1 <- top

     create a transpose of the graph (reverse the directions)

     1 <---- 2 <------ 4 <------- 5
     \     |^
      \>  /
        3

    dfs the transpose int the order of the toposort

    dfs from 1:
    1->3->2 // one component
    2 and 3 are alredy visited
    dfs from 4:
    4 // 2 is already visited so it is not added
    dfs from 5:
    5 // 4 is already visite
    these are the three components
  */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<int>& vis, stack<int>& topo, vector<int> adj[]) {
    vis[node] = true;

    for (auto it : adj[node]) {
        if (vis[it]) continue;

        dfs(it, vis, topo, adj);
    }

    topo.push(node);
}

void getComponent(int node, vector<int>& vis, vector<int> transpose[], vector<int>& component) {
    vis[node] = true;
    component.push_back(node);
    for (auto it : transpose[node]) {
        if (vis[it]) continue;
        getComponent(it, vis, transpose, component);
    }
}

vector<vector<int>> getSCC(vector<int> adj[], int nodes) {
    vector<vector<int>> scc;
    vector<int> vis(nodes, false);
    stack<int> topo;

    // get the topo sort
    for (int i = 0; i < nodes; i++) {
        if (vis[i] == false) {
            dfs(i, vis, topo, adj);
        }
    }

    // create transpose
    vector<int> transpose[nodes];
    for (int i = 0; i < nodes; i++) {
        for (auto it : adj[i]) {
            transpose[it].push_back(i);
        }
    }

    // run dfs according to the topo sort
    vis = vector<int>(nodes, false);

    while (topo.empty() == false) {
        int curr = topo.top();
        cout << curr << endl;
        topo.pop();

        if (vis[curr]) continue;

        vector<int> component;
        getComponent(curr, vis, transpose, component);
        scc.push_back(component);
    }

    return scc;
}

int main() {
    int nodes, edges; cin >> nodes >> edges;
    vector<int> adj[nodes];

    // directed graph
    for (int i = 0; i < edges; i++) {
        // u ----> v
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }

    auto scc = getSCC(adj, nodes);

    for (auto& v : scc) {
        cout << "[ ";
        for (auto& it : v) {
            cout << it + 1 << " ";
        }
        cout << "]";
    } cout << endl;

    return 0;
}

/*
5 5
1 2
2 3
3 1
2 4
4 5
Output:
[ 1 3 2 ][ 4 ][ 5 ]
 */