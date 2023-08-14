// Author: Anuj Jadhav


/**
 Range query 2D
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define deb(x) cout << #x << " = " << x << endl;
#define sz(str) str.length()
#define rep(i, n) for(ll i = 0; i < n; i++)

class SegmentTree2D {
public:

	vector<vector<int>> mat, tree;

	SegmentTree2D(vector<vector<int>> matrix) {
		mat = matrix;

		int rows = mat.size(), cols = matrix[0].size();
		while ((rows & (rows - 1)) != 0) {
			rows++;
			mat.push_back(vector<int>(cols, 0));
		}

		for (auto& v : mat) {
			int size = v.size();
			while ((size & (size - 1)) != 0) {
				v.push_back(0);
				size++;
			}
		}

		rows = mat.size(), cols = mat[0].size();
		tree = vector<vector<int>>(2 * rows - 1, vector<int>(2 * cols - 1));

		build();
	}

	void build() {
		int rows = mat.size();
		buildUtil(0, 0, rows - 1);
	}

	void constSegTree(int node, int start, int end, vector<int>& arr, vector<int>& tree) {
		if (start == end) {
			tree[node] = arr[start];
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
			constSegTree(leftChild, start, mid, arr, tree);
			constSegTree(rightChild, mid + 1, end, arr, tree);
			tree[node] = tree[leftChild] + tree[rightChild];
		}
	}

	void buildUtil(int node, int start, int end) {
		if (start == end) {
			int cols = mat[start].size();
			constSegTree(0, 0, cols - 1, mat[start], tree[node]);
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
			buildUtil(leftChild, start, mid);
			buildUtil(rightChild, mid + 1, end);

			// tree[node] = tree[leftChild] + tree[rightChild];
			int cols = tree[node].size();
			for (int i = 0; i < cols; i++)
				tree[node][i] = tree[leftChild][i] + tree[rightChild][i];
		}
	}

	void update(int row, int col, int val) {
		int rows = mat.size();
		updateUtil(0, 0, rows - 1, row, col, val);
	}

	void updateSegTree(int node, int start, int end, int idx, int val, vector<int>& tree) {
		if (start == end) {
			tree[node] = val;
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
			if (idx <= mid) updateSegTree(leftChild, start, mid, idx, val, tree);
			else updateSegTree(rightChild, mid + 1, end, idx, val, tree);
			tree[node] = tree[leftChild] + tree[rightChild];
		}
	}

	void updateUtil(int node, int start, int end, int row, int col, int val) {
		if (start == end) {
			int cols = mat[0].size();
			updateSegTree(0, 0, cols - 1, col, val, tree[node]);
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
			if (row <= mid) updateUtil(leftChild, start, mid, row, col, val);
			else updateUtil(rightChild, mid + 1, end, row, col, val);

			// tree[node] = tree[leftChild] + tree[rightChild];
			int cols = tree[node].size();
			for (int i = 0; i < cols; i++)
				tree[node][i] = tree[leftChild][i] + tree[rightChild][i];
		}
	}

	int sumSegTree(int node, int start, int end, int left, int right, vector<int>& tree) {
		if (end < left || right < start)
			return 0;
		if (left <= start && end <= right)
			return tree[node];
		int mid = start + (end - start) / 2;
		int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
		int leftSum = sumSegTree(leftChild, start, mid, left, right, tree);
		int rightSum = sumSegTree(rightChild, mid + 1, end, left, right, tree);
		return leftSum + rightSum;
	}

	int sumRegionUtil(int node, int start, int end, int row1, int col1, int row2, int col2) {
		int cols = mat[0].size();

		if (end < row1 || row2 < start)
			return 0;
		if (row1 <= start && end <= row2)
			return sumSegTree(0, 0, cols - 1, col1, col2, tree[node]);

		int mid = start + (end - start) / 2;
		int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
		int leftSum = sumRegionUtil(leftChild, start, mid, row1, col1, row2, col2);
		int rightSum = sumRegionUtil(rightChild, mid + 1, end, row1, col1, row2, col2);
		return leftSum + rightSum;
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int rows = mat.size();
		return sumRegionUtil(0, 0, rows - 1, row1, col1, row2, col2);
	}
};

void solution() {
	vector<vector<int>> mat = { {1, 2, 3}, {4, 5, 6} };
	SegmentTree2D st(mat);

	int val = st.sumRegion(0, 0, 1, 2);
	cout << val << endl;
	st.update(0, 1, 100);
	val = st.sumRegion(0, 0, 1, 2);
	cout << val << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll test = 1;
	while (test--) {
		solution();
	}

	return 0;
}