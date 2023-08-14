/*
	Link: https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-interview-prep/binary-lifting/kth-table-official/ojquestion
	video: youtube.com/watch?v=PE-kQVZxvWA&list=PL-Jc9J83PIiGC6uQ2CjMhSaWAcmjbAQfp
	LC Submission: https://leetcode.com/problems/kth-ancestor-of-a-tree-node/

	Logic:
	Normally to find the kth table we will jump k times
	Binary lifting reduces this time to log(k)

	How?
	Suppose we want to do 5 jumps
	Bin rep of 5: 101
	So here we will do two jumps: 4, 1

	Implement:
	We will precompute the 1, 2, 4, 8, 16 ..... acestors
	and we will use them

	How precompute
	1: direct parent array
	2: find 1st parent twice
	4: find 2nd parent twice
	8: find 4th parent twice
	.
	.
	.

	point: if suppose node has depth = 5, and we search for 6th table
	then we will return the 5th table only

	Easy hai ho jayega
*/

#include <bits/stdc++.h>
using namespace std;

class TreeAncestor {
public:
    vector<int> parent;
    vector<vector<int>> table;
    int tableSize;
    
    void build() {
        int nodes = parent.size();
        tableSize = log2(nodes) + 1;

        table = vector<vector<int>>(nodes, vector<int>(tableSize));
        
        for(int node = 0; node < nodes; node++) {
            table[node][0] = parent[node];
        }
        
        for(int node = 0; node < nodes; node++) {
            for(int k = 1; k < tableSize; k++) {
                if(table[node][k-1] == -1) table[node][k] = -1;
                else table[node][k] = table[table[node][k-1]][k-1];
            }
        }
    }
    
    TreeAncestor(int n, vector<int>& parent) {
        this->parent = parent;
        build();
    }
    
    int getKthAncestor(int node, int k) {
        for (int i = 0; i < tableSize; i++) {
            if ((k >> i) & 1) {
                node = table[node][i];
                if(node == -1) return -1;
            }
        }
        return node;
    }
};
