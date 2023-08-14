// TODO: Do a class based implementation

// Find LCA of two nodes

/*
	video: https://www.youtube.com/watch?v=FzOSaw55Tp8&list=PL-Jc9J83PIiGC6uQ2CjMhSaWAcmjbAQfp&index=2

	Logic:
	Firstly bring both on the same level
	(precompute level and parent of each node)

	then suppose the height is 16, and lca is at height 7 then

	can we jump 16? no (because both will be same)
	can we jump 8? no (same)
	can we jump 4? yes (not same) rem = 7 - 4 = 3
	can we jump 3? no (same)
	can we jump 2? yes (not same) rem = 3 - 2 = 1
	can we jump 1? no (same)

	after this out both nodes will be at just one level lower than ancestor

		lca
		/ \
	   a   b

	Easy hai ho jayega
*/

// Author: Anuj Jadhav

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> table;
int tableSize = 0;

bool getBit(int num, int i) {
	return (num & (1 << i));
}

vector<vector<int>> build(vector<int> parent) {
	int nodes = parent.size();
	while ((1 << tableSize) <= nodes) {
		tableSize++;
	}

	table = vector<vector<int>>(tableSize, vector<int>(nodes));
	for (int node = 0; node < nodes; node++) {
		table[0][node] = parent[node];
	}

	for (int k = 1; k < tableSize; k++) {
		for (int node = 0; node < nodes; node++) {
			table[k][node] = table[k - 1][table[k - 1][node]];
		}
	}

	return table;
}

int query(int node, int k) {
	for (int i = 0; i < tableSize; i++) {
		if (getBit(k, i)) {
			node = table[i][node];
		}
	}
	return node;
}

vector<vector<int>> adj;
vector<int> parent, level;

int getLca(int u, int v) {
	if (level[u] > level[v]) {
		int diff = level[u] - level[v];
		u = query(u, diff);
	} else if (level[u] < level[v]) {
		int diff = level[v] - level[u];
		v = query(v, diff);
	}

	if (u == v) return u;

	for (int i = tableSize - 1; i >= 0; i--) {
		int newu = query(u, i);
		int newv = query(v, i);

		if (newu == newv) {
			continue;
		} else {
			u = newu;
			v = newv;
		}
	}
	return parent[u];
}

void dfs(int node, int lev) {
	level[node] = lev;
	for (auto it : adj[node]) {
		parent[it] = node;
		dfs(it, lev + 1);
	}
}

void solve() {
	int n; cin >> n;

	level = vector<int>(n);
	parent = vector<int>(n);
	adj = vector<vector<int>>(n);
	parent[0] = 0;
	for (int i = 1; i < n; i++) {
		cin >> parent[i];
		adj[parent[i]].push_back(i);
	}

	dfs(0, 1);
	table = build(parent);

	int m; cin >> m;
	vector<int> v;
	for (int i = 0; i < m; i++) {
		int val; cin >> val;
		v.push_back(val);
	}

	int res = v[0];
	for (int i = 1; i < m; i++)
		res = getLca(res, v[i]);
	cout << res << endl;
}

int32_t main() {
	int test = 1;
	//  cin >> test;

	while (test--) {
		solve();
	}

	return 0;
}