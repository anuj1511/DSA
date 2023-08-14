/*
	https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-interview-prep/segment-tree/whats-at-idx-point-query-range-update-official/ojquestion
	You are given an array(of integers) of length n.
	You are required to answer q queries.

	Queries can be of two types
	0. 0 ind : In this you have to tell the value of arr[ind].
	1. 1 l r val: In this query u have to increase all elements in this interval [l, r] by val.

	To do the above task u have to create a datastructure as follows :-

	Implement the SegmentTree class:
	1. SegmentTree(int arr[]): Initializes the SegmentTree object with an array,
	2. void update(int l, int r, int val): increase all elements in this interval [l, r] by val,
	3. int query(int ind): return arr[ind].

	Range update point query
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#ifndef ONLINE_JUDGE
#define deb(x) cerr << #x <<" = "; _print(x); cerr << endl;
#define deb2(x, y) cerr << #x << " = "; _print(x); cerr << ", " << #y << " = "; _print(y); cerr << endl;
#define deb3(x, y, z) _print(x); cerr << " "; _print(y); cerr << " "; _print(z); cerr << endl;
#define deb4(a, b, c, d) _print(a); cerr << " "; _print(b); cerr << " "; _print(c); cerr << " "; _print(d); cerr << endl;
#define deb5(a, b, c, d, e) _print(a); cerr << " "; _print(b); cerr << " "; _print(c); cerr << " "; _print(d); cerr << " "; _print(e); cerr << endl;
#else
#define deb(x)
#define deb2(x, y)
#define deb3(x, y, z)
#define deb4(a, b, c, d)
#define deb5(a, b, c, d, e)
#endif

void _print(int x) { cerr << x; }
void _print(char x) { cerr << x; }
void _print(string x) { cerr << x; }
void _print(double x) { cerr << x; }
void _print(ull x) { cerr << x; }
void _print(lld x) { cerr << x; }

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);

template <class T, class V> void _print(pair <T, V> p) { cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}"; }
template <class T> void _print(vector <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(set <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(multiset <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print(map <T, V> v) { cerr << "[ "; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print(unordered_map <T, V> v) { cerr << "[ "; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }

class SegmentTree {
private:
	vector<int> lazy;
	vector<int> nums;

public:
	SegmentTree(vector<int>& arr) {
		nums = arr;
		int size = arr.size();
		while ((size & (size - 1)) != 0) {
			size++;
			nums.push_back(0);
		}
		int max_size = 2 * size - 1;
		lazy = vector<int>(max_size, 0);
		// no need to make build as we have to initialize it with 0
	}

private:
	void propagate(int node) {
		int leftChild = 2 * node + 1;
		int rightChild = 2 * node + 2;
		lazy[leftChild] += lazy[node];
		lazy[rightChild] += lazy[node];
		lazy[node] = 0;
	}

	void update(int left, int right, int val, int node, int start, int end) {
		// propagate lazy value if not leaf
		if (start != end)
			propagate(node);

		if (start > right || end < left) {
			// no intersection
			return;
		} else if (left <= start && end <= right) {
			// fully inside
			lazy[node] += val;
		} else {
			// partial intersection
			int leftChild = 2 * node + 1;
			int rightChild = 2 * node + 2;
			int mid = start + (end - start) / 2;
			update(left, right, val, leftChild, start, mid);
			update(left, right, val, rightChild, mid + 1, end);
		}
	}

	int query(int idx, int node, int start, int end) {
		if (start != end)
			propagate(node);

		if (start == end) {
			nums[start] += lazy[node];
			lazy[node] = 0;
			return nums[start];
		}

		int leftChild = 2 * node + 1;
		int rightChild = 2 * node + 2;
		int mid = start + (end - start) / 2;
		if (idx <= mid) {
			return query(idx, leftChild, start, mid);
		} else {
			return query(idx, rightChild, mid + 1, end);
		}
	}

public:
	void update(int left, int right, int val) {
		int size = nums.size();
		update(left, right, val, 0, 0, size - 1);
	}

	int query(int idx) {
		int size = nums.size();
		return query(idx, 0, 0, size - 1);
	}
};

void solution() {
	int n; cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	deb(arr);
	SegmentTree st(arr);
	/*
		1 idx -> gets the ith idx
		2 l r val -> adds val in range l-r
	*/

	int q; cin >> q;
	while (q--) {
		int type; cin >> type;

		if (type == 1) {
			int idx; cin >> idx;
			deb2(type, idx);
			int res = st.query(idx);
			deb(res);
		} else {
			int l, r, val; cin >> l >> r >> val;
			st.update(l, r, val);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll test;
	cin >> test;

	while (test--) {
		solution();
	}

	return 0;
}