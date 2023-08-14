//https://www.codingninjas.com/codestudio/problems/max-xor-queries_1382020?leftPanelTab=0

/*

Problem Statement
You are given an array/list ‘ARR’ consisting of ‘N’ non-negative integers. You are also given a list ‘QUERIES’ consisting of ‘M’ queries, where the ‘i-th’ query is a list/array of two non-negative integers ‘Xi’, ‘Ai’, i.e ‘QUERIES[i]’ = [‘Xi’, ‘Ai’].
The answer to the ith query, i.e ‘QUERIES[i]’ is the maximum bitwise xor value of ‘Xi’ with any integer less than or equal to ‘Ai’ in ‘ARR’.
You should return an array/list consisting of ‘N’ integers where the ‘i-th’ integer is the answer of ‘QUERIES[i]’.

Sample Input 1:
2
5 2
0 1 2 3 4
1 3
5 6
1 1
1
1 0
Sample Output 1:
3 7
-1

 */

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    vector<Node*> links;

    Node() {
        links.resize(2, NULL);
    }

    bool containsKey(int bit) {
        return links[bit] != NULL;
    }

    Node* get(int bit) {
        return links[bit];
    }

    void put(int bit, Node* node) {
        links[bit] = node;
    }
};

bool getBit(int num, int pos) {
    return (num & (1 << pos));
}

int setBit(int num, int pos) {
    return (num | (1 << pos));
}

Node* insert(Node* root, int num) {
    Node* node = root;
    for (int i = 31; i >= 0; i--) {
        int bit = getBit(num, i);
        if (node->containsKey(bit) == false) {
            node->put(bit, new Node());
        }
        node = node->get(bit);
    }
    return root;
}

int getMax(Node* root, int x) {
    int num = 0;
    Node* node = root;
    for (int i = 31; i >= 0; i--) {
        int bit = getBit(x, i);

        if (node->containsKey(1 - bit)) {
            num = setBit(num, i);
            node = node->get(1 - bit);
        } else {
            node = node->get(bit);
        }
    }
    return num;
}

vector<int> maxXorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    //	Write your coode here.
    vector<vector<int>> store;
    cout << "qs: " << queries.size() << endl;
    for (int i = 0; i < queries.size(); i++) {
        vector<int> v = queries[i];
        int x = v[0];
        int a = v[1];

        store.push_back({ a, x, i });
    }

    sort(store.begin(), store.end());
    sort(arr.begin(), arr.end());

    Node* root = new Node();
    int n = arr.size();
    vector<int> ans(queries.size());
    int idx = 0;

    for (int i = 0; i < store.size(); i++) {
        vector<int> v = store[i];
        int x = v[1];
        int a = v[0];
        int originalQuery = v[2];

        while (arr[idx] <= a) {
            root = insert(root, arr[idx]);
            idx++;
        }

        int val;
        if (idx == 0) {
            val = -1;
        } else {
            val = getMax(root, x);
        }

        ans[originalQuery] = val;
    }

    return ans;
}

/*
2
5 2
0 1 2 3 4
1 3
5 6
1 1
1
1 0 */

int main() {
    int n = 5;
    int q = 2;
    vector<int> arr = { 0,1,2,3,4 };
    vector<vector<int>> queries = { {1,3},{5,6} };
    vector<int> ans = maxXorQueries(arr, queries);

    for (auto it : ans) cout << it << " ";
    cout << endl;


    return 0;
}