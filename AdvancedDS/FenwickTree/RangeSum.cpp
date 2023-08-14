// Author: Anuj Jadhav

#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
	vector<int> bit;
	int size;

	FenwickTree(int n) {
		size = n;
		bit = vector<int>(size + 1);
	}

	void update(int idx, int val) {
		idx++;
		while(idx <= size) {
			bit[idx] += val;
			idx += (idx & (-idx));
		}
	}

	int query(int idx) {
		idx++;
		int ans = 0;
		while(idx > 0) {
			ans += bit[idx];
			idx -= (idx & (-idx));
		}
		return ans;
	} 
};

void solution() {
	int n; cin >> n; 
	vector<int> arr(n);
	for(auto &it: arr) cin >> it;

	FenwickTree ft(n);
	for(int i = 0; i < n; i++) 
		ft.update(i, arr[i]);

	int queries; cin >> queries;

	for(int i = 0; i < queries; i++) {
		int type; cin >> type;
		if(type == 1) {
			// range sum
			int l, r; cin >> l >> r;
			int res = ft.query(r) - ft.query(l-1);
			cout << res << endl;
		} else if(type == 2) {
			// update
			int idx, newVal; cin >> idx >> newVal;
			int oldVal = arr[idx];
			ft.update(idx, -oldVal);
			arr[idx] = newVal;
			ft.update(idx, newVal);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int test;
	cin >> test;

	while (test--) {
		solution();
	}

	return 0;
}

/*
Input:

1
4
1 2 3 4
4
1
0 3
2
0 5
1 
0 0
1
0 3

Output:
10
5
14

*/