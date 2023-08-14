// Author: Anuj Jadhav
// https://www.youtube.com/watch?v=dQw4w9WgXcQ

#include <bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long 

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi adj;
vi height, level, maxHeight;

void dfs1(int node, int par, int lev) {
	int childMax = 0;
	level[node] = lev;
	for (auto it : adj[node]) {
		if (it == par) continue;
		dfs1(it, node, lev + 1);
		childMax = max(childMax, height[it]);
	}
	height[node] = 1 + childMax;
}

void dfs2(int node, int par, int upper) {
	int first = -1, second = -1;
	for (auto it : adj[node]) {
		if (it == par) continue;
		if (first == -1 || height[it] > height[first]) {
			second = first;
			first = it;
		} else if (second == -1 || height[it] > height[second]) {
			second = it;
		}
	}

	int firstMax = (first == -1) ? 0 : height[first];
	int secondMax = (second == -1) ? 0 : height[second];

	int currMaxHeight = 1 + max({ firstMax, secondMax, upper });
	maxHeight[node] = currMaxHeight;

	for (auto it : adj[node]) {
		if (it == par) continue;
		if (it != first) {
			dfs2(it, node, max(upper, firstMax) + 1);
		} else {
			dfs2(it, node, max(upper, secondMax) + 1);
		}
	}
}

void solution() {
	int n; cin >> n;
	adj = vvi(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	height = level = maxHeight = vector<int>(n);

	dfs1(0, -1, 0);
	dfs2(0, -1, 0);

	for (auto it : maxHeight) cout << it << " ";
	cout << endl;
}

int32_t main() {
	// #ifndef ONLINE_JUDGE
	//	 freopen("Error.txt", "w", stderr);
	// #endif
	fastio();

	int test = 1;

	while (test--) {
		solution();
	}

	return 0;
}

/*
Input:
7
0 1
0 2
2 3
2 4
2 5
5 6

Tree: 

			0
		/      \
	  1          2
	         /   |   \
			3    4    5
			           \
					    6	

Output:
4 5 3 4 4 4 5
*/