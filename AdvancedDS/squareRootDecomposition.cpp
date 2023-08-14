#include <bits/stdc++.h>
using namespace std;

class sqrtDecomposition {
public:
    vector<int> block;
    int len;
    vector<int> arr;
    sqrtDecomposition(vector<int> arr) {
        len = ceil(sqrt(arr.size()));
        block.resize(len, INT_MAX);
        this->arr = arr;
        build();
    }

    void build() {
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            int sqrtIdx = i / len;
            block[sqrtIdx] = min(block[sqrtIdx], arr[i]);
        }
    }

    int query(int l, int r) {
        int ans = INT_MAX;
        while (l <= r) {
            if (l % len == 0 && l + len - 1 <= r) {
                int sqrtIdx = l / len;
                ans = min(ans, block[sqrtIdx]);
                l += len;
            } else {
                ans = min(ans, arr[l]);
                l++;
            }
        }
        return ans;
    }
};

void solution() {
    vector<int> arr = { 2,3,-1,9,6,-2,10,4,12,-1,5,7,16,-4,8,3 };
    sqrtDecomposition sd(arr);
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            cout << i << " " << j << " " << sd.query(i, j) << endl;
        }
    }
}

int main() {
    solution();
    return 0;
}