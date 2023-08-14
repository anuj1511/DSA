// Author: Anuj Jadhav


/**
 Range query, point update
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define deb(x) cout << #x << " = " << x << endl;
#define sz(str) str.length()
#define rep(i, n) for(ll i = 0; i < n; i++)

class SegmentTree {
public:
    vector<int> nums;
    vector<int> tree;

    SegmentTree(vector<int>& nums) {
        int sz = nums.size();
        while ((sz & (sz - 1)) != 0) {
            sz++;
            nums.push_back(0);
        }
        this->nums = nums;
        int treeSize = 2 * sz - 1;
        tree = vector<int>(treeSize);
        build();
    }

    void build() {
        int sz = nums.size();
        build(0, 0, sz - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = start + (end - start) / 2;
            int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
            build(leftChild, start, mid);
            build(rightChild, mid + 1, end);
            tree[node] = tree[leftChild] + tree[rightChild];
        }
    }

    void update(int index, int val) {
        int sz = nums.size();
        update(0, 0, sz - 1, index, val);
    }

    void update(int node, int start, int end, int index, int val) {
        if (start == end) {
            tree[node] = val;
            nums[start] = val;
        } else {
            int mid = start + (end - start) / 2;
            int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
            if (index <= mid) update(leftChild, start, mid, index, val);
            else update(rightChild, mid + 1, end, index, val);
            tree[node] = tree[leftChild] + tree[rightChild];
        }
    }

    int query(int left, int right) {
        int sz = nums.size();
        return query(0, 0, sz - 1, left, right);
    }

    int query(int node, int start, int end, int left, int right) {
        if (end < left || right < start)
            return 0;
        if (left <= start && end <= right)
            return tree[node];
        int mid = start + (end - start) / 2;
        int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        int leftSum = query(leftChild, start, mid, left, right);
        int rightSum = query(rightChild, mid + 1, end, left, right);
        return leftSum + rightSum;
    }
};

void solution() {

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