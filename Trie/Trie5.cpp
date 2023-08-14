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