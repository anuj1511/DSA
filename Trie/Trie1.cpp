#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

/*
    Insert
    Search
    Check if prefix exists
*/

class Node {
public:
    Node* links[26];
    bool flag;

    Node() {
        for (int i = 0; i < 26; i++) {
            links[i] = NULL;
        }
        flag = false;
    }

    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL);
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
        for (int i = 0; i < word.size(); i++) {
            if (node->containsKey(word[i]) == false) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    bool search(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (node->containsKey(word[i]) == false) {
                return false;
            }
            node = node->get(word[i]);
        }

        return node->isEnd();
    }

    bool startsWith(string prefix) {
        Node* node = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (node->containsKey(prefix[i]) == false) {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }
};



int main() {

    return 0;
}