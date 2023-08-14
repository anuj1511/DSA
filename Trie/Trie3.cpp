#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

/*
    Complete String: every prefix of the
    string is also present in the array

    Q) We want to return the longest string.
    if multiple strings exist we will return
    lexographically smallest, if no string exist
    return "None"

    E.g.: "n", "ninja", "ninj", "ni", "nin", "ninga"
    Ans: "ninja"

    Approach:
        1) Insert all the string into trie.
        2) For each string check if it is complete.
        3) Store string
 */

class Node {
    vector<Node*> links;
    bool flag;

public:
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

class Trie {
public:
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            if (node->containsKey(ch) == false) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->setEnd();
    }

    bool isComplete(string str) {
        Node* node = root;
        for (char ch : str) {
            if (node->containsKey(ch) == false) {
                return false;
            }
            node = node->get(ch);
            if (node->isEnd() == false) {
                return false;
            }
        }
        return true;
    }

    string completeString(int n, vector<string>& v) {
        string res = "";
        for (int i = 0; i < n; i++) {
            string curr = v[i];
            if (isComplete(curr)) {
                if (curr.size() > res.size()) {
                    res = curr;
                } else if (curr.size() == res.size() && curr < res) {
                    res = curr;
                }
            }
        }
        return res;
    }
};

string completeString(int n, vector<string>& v) {
    Trie t;
    for (int i = 0; i < n; i++) {
        t.insert(v[i]);
    }

    string ans = t.completeString(n, v);

    if (ans == "") return "None";
    return ans;
}

int main() {
    vector<string> v = { "n", "ninja", "ninj", "ni", "nin", "ning", "ninga" };
    int n = v.size();

    cout << completeString(n, v) << endl;

    return 0;
}

/*

    string completeStringUtil(Node* node, string temp) {
        cout << temp << endl;
        if (node != root && node->isEnd() == false) {
            temp.pop_back();
            return temp;
        }

        string res = temp;
        for (int i = 0; i < 26; i++) {
            char ch = i + 'a';
            if (node->containsKey(ch) == false) continue;
            temp.push_back(ch);
            cout << temp << endl;
            string curr = completeStringUtil(root->get(ch), temp);
            temp.pop_back();

            if (curr.size() > res.size()) {
                res = curr;
            }
        }
        return res;
    }

    string completeString() {
        Node* node = root;
        string res = completeStringUtil(root, "");
        return res;
    }

 */