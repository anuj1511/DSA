// Author: Anuj Jadhav

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define deb(x) cout << #x << " = " << x << endl;
#define sz(str) str.length()
#define rep(i, n) for(ll i = 0; i < n; i++)


/*
						 2, 1
			3, 2                        2, 1
	  3, 1        3, 1        2, 1             inf, 2
	3    4      3    5      2     inf      inf    inf


						0, 1
			0, 1                        2, 1
	  0, 1        3, 1        2, 1             inf, 2
	0    4      3    5      2     inf      inf    inf
*/

class SegmentTree {
public:
	// minimum number, freq of number
	vector<pair<int, int>> tree;
	vector<int> nums;

	SegmentTree(vector<int>& arr) {
		nums = arr;
		int size = nums.size();
		while ((size & (size - 1)) != 0) {
			nums.push_back(INT_MAX);
			size++;
		}

		int treeSize = 2 * size - 1;
		tree = vector<pair<int, int>>(treeSize);
		build(0, 0, size - 1);
	}

	void build(int node, int start, int end) {
		if (start == end) {
			tree[node] = { nums[start], 1 };
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1;
			int rightChild = 2 * node + 2;
			build(leftChild, start, mid);
			build(rightChild, mid + 1, end);

			pair<int, int> left = tree[leftChild];
			pair<int, int> right = tree[rightChild];

			int minLeft = left.first, leftFreq = left.second;
			int minRight = right.first, rightFreq = right.second;

			if (minLeft == minRight) tree[node] = { minLeft, leftFreq + rightFreq };
			else if (minLeft < minRight) tree[node] = left;
			else tree[node] = right;
		}
	}

	void update(int idx, int val) {
		int size = nums.size();
		update(idx, val, 0, 0, size - 1);
	}

	void update(int idx, int val, int node, int start, int end) {
		if (start == end) {
			nums[idx] = val;
			tree[node] = { val, 1 };
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1;
			int rightChild = 2 * node + 2;

			if (idx <= mid)
				update(idx, val, leftChild, start, mid);
			else
				update(idx, val, rightChild, mid + 1, end);

			pair<int, int> left = tree[leftChild];
			pair<int, int> right = tree[rightChild];

			int minLeft = left.first, leftFreq = left.second;
			int minRight = right.first, rightFreq = right.second;

			if (minLeft == minRight) tree[node] = { minLeft, leftFreq + rightFreq };
			else if (minLeft < minRight) tree[node] = left;
			else tree[node] = right;
		}
	}

	pair<int, int> query(int left, int right) {
		int size = nums.size();
		return query(left, right, 0, 0, size - 1);
	}

	pair<int, int> query(int left, int right, int node, int start, int end) {
		if (end < left || right < start) {
			return { INT_MAX, 1 };
		} else if (left <= start && end <= right) {
			return tree[node];
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1;
			int rightChild = 2 * node + 2;

			pair<int, int> leftRes = query(left, right, leftChild, start, mid);
			pair<int, int> rightRes = query(left, right, rightChild, mid + 1, end);

			int minLeft = leftRes.first, leftFreq = leftRes.second;
			int minRight = rightRes.first, rightFreq = rightRes.second;

			pair<int, int> res;

			if (minLeft == minRight) res = { minLeft, leftFreq + rightFreq };
			else if (minLeft < minRight) res = leftRes;
			else res = rightRes;

			return res;
		}
	}
};

void solution() {
	int n, q; cin >> n >> q;
	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];

	SegmentTree st(nums);

	while (q--) {
		int type; cin >> type;

		if (type == 1) {
			int idx, val; cin >> idx >> val;
			st.update(idx, val);
		} else {
			int left, right; cin >> left >> right;
			right--;
			pair<int, int> res = st.query(left, right);
			cout << res.first << " " << res.second << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll test = 1;
	// cin >> test;

	while (test--) {
		solution();
	}

	return 0;
}