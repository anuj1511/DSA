// Find LCA of two nodes
// Author: Anuj Jadhav

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

vector<int> depth, parent, subtree, heavy;

void dfs(int node, int dep) {
	depth[node] = dep;
	subtree[node] = 1;

	for (auto child : adj[node]) {
		dfs(child, dep + 1);

		subtree[node] += subtree[child];

		if (subtree[child] > subtree[heavy[node]]) {
			heavy[node] = child;
		}
	}
}

vector<int> head, lt, pos;
int idx;

void dfsHLD(int node, int chain) {
	head[node] = chain;
	// lt[idx] = value[node];
	pos[node] = idx;
	idx++;

	if (heavy[node] != 0) {
		dfsHLD(heavy[node], chain);
	}
	for (auto child : adj[node]) {
		if (child == heavy[node]) continue;
		dfsHLD(child, child);
	}
}

int getLca(int u, int v) {
	while (head[u] != head[v]) {
		if (depth[head[u]] < depth[head[v]]) {
			swap(u, v);
		}
		u = parent[head[u]];
		// extra line in future
	}

	if (depth[u] > depth[v])
		swap(u, v);

	// depth[u] < depth[v]
	return u;
}