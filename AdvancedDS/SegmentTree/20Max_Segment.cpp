#include <bits/stdc++.h>
using namespace std;

#define int long long
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

// Max Segment
class SegmentTree {
public:
	vector<int> nums;
	vector<int> sum, pref, suff, seg;

	SegmentTree(vector<int> nums) {
		int sz = nums.size();
		while ((sz & (sz - 1)) != 0) {
			sz++;
			nums.push_back(0);
		}
		this->nums = nums;
		int treeSize = 2 * sz - 1;
		sum = pref = suff = seg = vector<int>(treeSize);
		build();
	}

	void build() {
		int sz = nums.size();
		build(0, 0, sz - 1);
	}

	void build(int node, int start, int end) {
		if (start == end) {
			sum[node] = pref[node] = suff[node] = seg[node] = nums[start];
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
			build(leftChild, start, mid);
			build(rightChild, mid + 1, end);
			seg[node] = max({ seg[leftChild], seg[rightChild], suff[leftChild] + pref[rightChild] });
			pref[node] = max(pref[leftChild], sum[leftChild] + pref[rightChild]);
			suff[node] = max(suff[rightChild], suff[leftChild] + sum[rightChild]);
			sum[node] = sum[leftChild] + sum[rightChild];
		}
	}

	void update(int index, int val) {
		int sz = nums.size();
		update(0, 0, sz - 1, index, val);
	}

	void update(int node, int start, int end, int index, int val) {
		if (start == end) {
			nums[start] = val;
			sum[node] = pref[node] = suff[node] = seg[node] = val;
		} else {
			int mid = start + (end - start) / 2;
			int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
			if (index <= mid) update(leftChild, start, mid, index, val);
			else update(rightChild, mid + 1, end, index, val);
			seg[node] = max({ seg[leftChild], seg[rightChild], suff[leftChild] + pref[rightChild] });
			pref[node] = max(pref[leftChild], sum[leftChild] + pref[rightChild]);
			suff[node] = max(suff[rightChild], suff[leftChild] + sum[rightChild]);
			sum[node] = sum[leftChild] + sum[rightChild];
		}
	}

	int query() {
		return max(0LL, seg[0]);
	}
};

int32_t main() {
	int n, q; cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];
	SegmentTree st(arr);
	cout << st.query() << endl;
	while (q--) {
		int idx, val; cin >> idx >> val;
		st.update(idx, val);
		cout << st.query() << endl;
	}
	return 0;
}