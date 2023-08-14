// Given two strings, one is a text string, txtand other is a pattern string, pat.The task is to print the indexes of all the occurences of pattern string in the text string.For printing, Starting Index of a string should be taken as 1.


// Example 1:

// Input:
// txt = "batmanandrobinarebat", pat = "bat"
// Output : 1 18
// Explanation : The string "bat" occurs twice
// in txt, one starts are index 1 and the other
// at index 18.

#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for(ll i = 0; i < n; i++)

vector<int> computeLPS(string pat) {
    int m = pat.size();
    vector<int> lps(m);
    lps[0] = 0;

    int i = 1;
    int len = 0;
    while (i < m) {
        if (pat[i] == pat[len]) {
            lps[i] = len + 1;
            len += 1;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                i++;
            }
        }
    }

    return lps;
}

vector<int> KMP(string pat, string txt) {
    vector<int> lps = computeLPS(pat);

    int n = txt.size(), m = pat.size();

    int i = 0, j = 0;
    vector<int> res;

    while (i < n) {
        if (txt[i] == pat[j]) {
            i++, j++;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }

        if (j == m) {
            res.push_back(i - j + 1);
            j = lps[j - 1];
        }

    }

    return res;
}

int main() {
    string txt = "batmanandrobinarebat";
    string pat = "bat";
    vector<int> ans = KMP(pat, txt);
    for (auto it : ans) {
        cout << it << " ";
    } cout << endl;
    return 0;
}