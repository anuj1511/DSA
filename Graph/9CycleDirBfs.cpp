#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
    Approach:
        Using Kahn's Algo
        if len of topo sort == V
            no cycle so return false
        else
            there is a cycle
 */

bool isCycle(vector<vector<int>> adj, int v) {
    vector<int> indegree(v + 1, 0);
    vector<int> topo;

    for (int i = 1; i <= v; i++) {
        for (int it : adj[i]) {
            indegree[it]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= v; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (q.empty() == false) {
        int curr = q.front();
        topo.push_back(curr);
        q.pop();

        for (int it : adj[curr]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it);
            }
        }
    }

    if (topo.size() == v) {
        return false;
    } else {
        return true;
    }
}

int main() {

    return 0;
}