# **Different ways to find LCA**

All the codes provided are submitted on: [Coding Ninja: LCA - Lowest Common Ancestor](https://www.codingninjas.com/studio/problems/lca-lowest-common-ancestor_2443409?leftPanelTab=0)

## **1. Brute Force**

**Approach:**

- Calculate the parent and depth of all nodes in the tree using depth-first search (DFS).
- For each LCA query:
	- a. Ensure both nodes have the same depth by moving the deeper node upwards.
	- b. Move both nodes up simultaneously until they meet at the LCA node.

# Complexity
- Time complexity: 
	For each query: `O(h)` where `h` is the height of the tree (In worst case h = n)
	Overall time complexity: O(q * h)

- Space complexity: 
	`O(n)` - to store adj, depth, and parent array

**Code (C++):**

```cpp
vector<vector<int>> adj;
vector<int> parent, depth;

int getLCABrute(int u, int v) {
	while(depth[u] > depth[v]) {
		u = parent[u];
	}

	while(depth[v] > depth[u]) {
		v = parent[v];
	}

	while(u != v) {
		u = parent[u];
		v = parent[v];
	}

	return u;
}

void dfs(int node, int par, int lev) {
	parent[node] = par;
	depth[node] = lev;
	for(auto child: adj[node]) 
		if(child != par)
			dfs(child, node, lev + 1);
}

vector<int> lca(int n, vector<vector<int>> edges, vector<vector<int>> query) {
	adj = vector<vector<int>>(n);
	depth = vector<int>(n);
	parent = vector<int>(n);

	for(auto edge: edges) {
		int u = edge[0], v = edge[1];
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, 0, 1);

	vector<int> res;

	for(auto quer: query) {
		int u = quer[0], v = quer[1];
		u--, v--;
		int lca = getLCABrute(u, v);
		res.push_back(lca + 1);
	}

	return res;
}
```

## **2. Using Binary Lifting**

**Approach:**

- Calculate the parent and depth of all nodes in the tree using depth-first search (DFS).
- Create a sparse table that stores the jump as a power of 2.
- For each query:
  - a. Lift the deeper node by calculating the difference between the deeper and upper one.
  - b. Keep jumping from max jump to 0, ensuring they do not reach the same node.
  - c. At the end, both nodes will reach just below the LCA. You can then simply return the parent of u or v.

# Complexity
- Time complexity: 
	For each query: `O(log(h))` where `h` is the height of the tree (In worst case h = n)
	Overall time complexity: O(q * log(h))

- Space complexity: 
	`O(nlog(n) + n + n + n)` - `nlog(n)` for sparse table, and `n` for adj, parent, depth

**Code (C++):**

```cpp
vector<vector<int>> adj;
vector<int> parent, depth;

vector<vector<int>> table;
int tableSize;

void fillTable(vector<int>& parent) {
	int n = parent.size();
	tableSize = ceil(log2(n));

	table = vector<vector<int>>(n, vector<int>(tableSize + 1));

	for(int node = 0; node < n; node++) {
		table[node][0] = parent[node];
	}

	for(int k = 1; k <= tableSize; k++)
		for(int node = 0; node < n; node++)
			table[node][k] = table[table[node][k-1]][k-1];
}

int query(int node, int jump) {
	for(int i = tableSize; i >= 0; i--)
		if(jump & (1 << i))
			node = table[node][i];
	return node;
}

int getLCABinaryLifting(int u, int v) {
	if(depth[u] > depth[v]) {
		int diff = depth[u] - depth[v];
		u = query(u, diff);
	}

	if(depth[v] > depth[u]) {
		int diff = depth[v] - depth[u];
		v = query(v, diff);
	}

	if(u == v) return u;

	for(int i = tableSize; i >= 0; i--) {
		int newu = table[u][i];
		int newv = table[v][i];

		if(newu == newv) continue;
		u = newu;
		v = newv;
	}

	return parent[u];
}

void dfs(int node, int par, int lev) {
	parent[node] = par;
	depth[node] = lev;
	for(auto child: adj[node]) 
		if(child != par)
			dfs(child, node, lev + 1);
}

vector<int> lca(int n, vector<vector<int>> edges, vector<vector<int>> query) {
	adj = vector<vector<int>>(n);
	depth = vector<int>(n);
	parent = vector<int>(n);
	for(auto edge: edges) {
		int u = edge[0], v = edge[1];
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, 0, 1);
	fillTable(parent);

	vector<int> res;

	for(auto quer: query) {
		int u = quer[0], v = quer[1];
		u--, v--;
		int lca = getLCABinaryLifting(u, v);
		res.push_back(lca + 1);
	}

	return res;
}
```

## **3. Using Is Ancestor**

**Approach:**

- Calculate the `tin` (entry time) and `tout` (exit time) of all nodes in the tree using depth-first search (DFS).
- Create a sparse table along with DFS that stores the jump as a power of 2.
- Implement a function `isAncestor` to determine if one node is an ancestor of another. This function uses the logic that the entry and exit times of the child will fall within the range of the entry and exit times of the parent.
- For each LCA query:
  - a. Check if `u` is a parent of `v` and vice versa. If either is a parent of the other, return the parent as the LCA.
  - b. For one of the nodes, move it upward just enough so that it is not the ancestor of the other node.
  - c. The immediate parent of the node that was moved upward will be the LCA.

# Complexity
- Time complexity: 
	For each query: `O(log(h))` where `h` is the height of the tree (In worst case h = n)
	Overall time complexity: O(q * log(h))

- Space complexity: 
	`O(nlog(n) + n + n + n)` - `nlog(n)` for sparse table, and `n` for adj, tin, tout

**Code (C++):**

```cpp
vector<vector<int>> adj;
vector<int> tin, tout;
vector<vector<int>> table;
int timer, tableSize;

void dfs(int node, int par) {
	tin[node] = timer++;

	table[node][0] = par;
	for(int i = 1; i <= tableSize; i++) 
		table[node][i] = table[table[node][i-1]][i-1];

	for(int child: adj[node])
		if(child != par)
			dfs(child, node);
	
	tout[node] = timer++;
}

void preprocess(int n) {
	tin = tout = vector<int>(n);
	timer = 0;
	tableSize = ceil(log2(n));
	table = vector<vector<int>>(n, vector<int>(1 + tableSize));
	dfs(0, 0);
}

bool isAncestor(int par, int child) {
	return tin[par] <= tin[child] && tout[child] <= tout[par];
}

int getLCA(int u, int v) {
	if(isAncestor(u, v))
		return u;
	if(isAncestor(v, u))
		return v;

	for(int i = tableSize; i >= 0; i--)
		if(isAncestor(table[u][i], v) == false)
			u = table[u][i];

	return table[u][0];
}

vector<int> lca(int n, vector<vector<int>> edges, vector<vector<int>> query) {
	adj = vector<vector<int>>(n);
	for(auto edge: edges) {
		int u = edge[0], v = edge[1];
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	preprocess(n);

	vector<int> res;
	for(auto quer: query) {
		int u = quer[0], v = quer[1];
		u--, v--;
		int lca = getLCA(u, v);
		res.push_back(1 + lca);
	}

	return res;
}
```

## **4. Using Heavy-Light Decomposition**

**Approach:**

- Calculate essential information for each node in the tree using depth-first search (DFS):
  - `parent`: Stores the parent of each node.
  - `depth`: Records the depth of each node in the tree.
  - `subtree`: Represents the total number of nodes in the subtree rooted at a given node, including itself.
  - `heavy`: Identifies the child node with the maximum subtree size, effectively designating the heavy child.

- Assign head values to each node to organize them into chains:
  - Chains help break the tree into smaller sections.
  - Nodes in the same chain share the same head.
  - Heavy nodes become the part of the current chain.
  - For non-heavy nodes, new chains start from them.

- For each LCA query:
  - Check if both nodes are part of the same chain.
    - If they are, return the node with the higher level (lower depth).
  - If they are in different chains:
    - Move the node with the lower chain head upwards towards the parent of its chain head.
    - Repeat this process until both nodes are in the same chain.
  - Finally, return the node with the higher position in the chain hierarchy as the LCA.

# Complexity
- Time complexity: 
	For each query: `O(log(h))` where `h` is the height of the tree (In worst case h = n)
	Overall time complexity: O(q * log(h))

- Space complexity: 
	`O(n)` -  to be precise `O(6 * n)` to store adj, depth, parent, subtree, heavy, head

**Code (C++):**

```cpp
vector<vector<int>> adj;
vector<int> depth, parent, subtree, heavy; // filler by dfs
vector<int> head; // filled by dfsHLD

void dfs(int node, int dep) {
	subtree[node] = 1;
	int heavyChild = -1, heavyWt = -1;
	
	for(auto child: adj[node]) {
		if(child == parent[node]) continue;
		parent[child] = node;
		depth[child] = dep + 1;

		dfs(child, dep + 1);
		
		subtree[node] += subtree[child];

		if(subtree[child] > heavyWt) {
			heavyWt = subtree[child];
			heavyChild = child;
		}
	}
	heavy[node] = heavyChild;
}

void dfsHLD(int node, int chain) {
	head[node] = chain;

	if(heavy[node] != -1)
		dfsHLD(heavy[node], chain);
	
	for(int child: adj[node]) {
		if(child == heavy[node] || child == parent[node]) continue;
		dfsHLD(child, child);
	}
}

int getLCA(int u, int v) {
	while(head[u] != head[v]) {
		if(depth[head[u]] < depth[head[v]]) 
			swap(u, v);
		u = parent[head[u]];
	}
	if(depth[u] > depth[v])
		swap(u, v);
	return u;
}

vector<int> lca(int n, vector<vector<int>> edges, vector<vector<int>> query) {
	adj = vector<vector<int>>(n);
	depth = parent = subtree = heavy = head = vector<int>(n);
	
	for(auto edge: edges) {
		int u = edge[0], v = edge[1];
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
 	dfs(0, 0);
	dfsHLD(0, 0);

	vector<int> res;

	for(auto quer: query) {
		int u = quer[0], v = quer[1];
		u--, v--;
		int lca = getLCA(u, v);
		res.push_back(1 + lca);
	}

	return res;
}
```
