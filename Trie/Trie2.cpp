#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

/*
    Insert
    Count how many times it is inserted
    Count words starting with prefix
    Erase
 */

class Node {
    Node* links[26];
    int endCount;
    int prefixCount;

public:
    Node() {
        for (int i = 0; i < 26; i++) {
            links[i] = NULL;
        }
        endCount = 0;
        prefixCount = 0;
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

    void incrementEnd() {
        endCount++;
    }

    void decrementEnd() {
        endCount--;
    }

    void incrementPrefix() {
        prefixCount++;
    }

    void decrementPrefix() {
        prefixCount--;
    }

    int getEndCount() {
        return endCount;
    }

    int getPrefixCount() {
        return prefixCount;
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
            node->incrementPrefix();
        }
        node->incrementEnd();
    }

    int countWordsEqualTo(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (node->containsKey(word[i]) == false) {
                return 0;
            }
            node = node->get(word[i]);
        }
        return node->getEndCount();
    }

    int countWordsStartingWith(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (node->containsKey(word[i]) == false) {
                return 0;
            }
            node = node->get(word[i]);
        }
        return node->getPrefixCount();
    }

    void erase(string word) {
        if (countWordsEqualTo(word) == 0) return;

        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            node = node->get(word[i]);
            node->decrementPrefix();
        }
        node->decrementEnd();
    }
};

int main() {
    Trie t;
    t.insert("apple");
    t.insert("apple");
    t.insert("apps");
    cout << t.countWordsEqualTo("apple") << endl;
    cout << t.countWordsStartingWith("app") << endl;
    t.erase("apple");
    t.erase("apple");
    cout << t.countWordsEqualTo("apple") << endl;
    cout << t.countWordsStartingWith("app") << endl;
    return 0;
}