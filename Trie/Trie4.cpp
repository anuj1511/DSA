#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

/*
Count number of Distinct Substring in a String

Difficulty Level : Easy
Last Updated : 22 Jun, 2022
Given a string, count all distinct substrings of the given string.
Examples:


Input : abcd
Output : abcd abc ab a bcd bc b cd c d
All Elements are Distinct

Input : aaa
Output : aaa aa a aa a a
All elements are not Distinct
 */

class Node {
public:
    vector<Node*> links;
    bool flag;

    Node() {
        links.resize(26, NULL);
        flag = false;
    }

    bool containsKey(char ch) {
        return links[ch - 'a'] != NULL;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

int countDistinct(string str) {
    Node* root = new Node();
    int count = 0;
    for (int i = 0; i < str.size(); i++) {
        Node* node = root;
        for (int j = i; j < str.size(); j++) {
            char ch = str[j];
            if (node->containsKey(ch) == false) {
                node->put(ch, new Node());
                count++;
            }
            node = node->get(ch);
        }
    }
    return count;
}

int main() {
    string str = "abab";
    cout << "count: " << countDistinct(str) << endl;

    return 0;
}