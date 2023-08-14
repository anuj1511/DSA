#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
using namespace std;

// to find max in a range l to r 

class SegmentTree {
public:
    vector<int> tree, arr;

    SegmentTree(vector<int> arr) {
        this->arr = arr;
        //Maximum size of segment tree = 2 * 2 ^ (log2(n))
        int x = (int)(ceil(log2(arr.size())));
        int max_size = 2 * (int)pow(2, x) - 1;
        tree.resize(max_size + 1);
        build(1, 0, arr.size() - 1);
    }

public:
    int query(int l, int r) {
        return query(1, 0, arr.size() - 1, l, r);
    }

public:
    void update(int idx, int val) {
        update(1, 0, arr.size() - 1, idx, val);
    }

private:
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int left = 2 * node;
            int right = 2 * node + 1;
            int mid = start + (end - start) / 2;
            build(left, start, mid);
            build(right, mid + 1, end);
            tree[node] = max(tree[left], tree[right]);
        }
    }

private:
    int query(int node, int start, int end, int l, int r) {

        if (end < l || start > r) {
            return INT_MIN;
        }

        if (l <= start && end <= r || start == end) {
            return tree[node];
        } else {
            int mid = start + (end - start) / 2;
            int left = query(2 * node, start, mid, l, r);
            int right = query(2 * node + 1, mid + 1, end, l, r);
            return max(left, right);
        }
    }

private:
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = start + (end - start) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            int left = tree[2 * node];
            int right = tree[2 * node + 1];
            tree[node] = max(left, right);
        }
    }
};

int main() {
    vector<int> arr = { 8, 7, 4, 2, 5, 3, 1, 10 };

    return 0;
}