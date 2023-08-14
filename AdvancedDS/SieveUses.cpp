/*
    This file contains different thing that we can calculate using sieve
    1. smallest prime divisor
    2. No. of prime factors of the number
    3. Sum of prime factors of the number
*/


#include <bits/stdc++.h>
using namespace std;

#define deb(x) cerr << #x <<" = "; _print(x); cerr << endl;

void _print(vector<int>& arr) {
    for(auto it: arr) cout << it << " ";
}

class Sieve {
public:
    vector<int> sieve; // isPrime or not
    vector<int> sumOfPFac; // sum of all prime factors (distinct)
    vector<int> noOfPFac; // no of prime factors
    vector<int> spm; // smallest prime multiple
    int n;

    Sieve(int n) {
        this->n = n;
        init();
    }

private:
    void init() {
        sieve = vector<int>(n + 1, true); // is prime or not
        sumOfPFac = vector<int>(n + 1);   // sum of distinct prime no.
        noOfPFac = vector<int>(n + 1);    // no of prime factors (repeated count)
        spm = vector<int>(n + 1);         // smallest prime multiple

        sieve[0] = sieve[1] = false;
        for (int i = 2; i <= n; i++) {
            if (sieve[i]) {
                spm[i] = i;
                sumOfPFac[i] = i;
                for (int j = i + i; j <= n; j += i) {
                    sieve[j] = false;
                    sumOfPFac[j] += i;
                    if (spm[j] == 0) spm[j] = i;
                }
            }
        }
        noOfPFac[1] = 0;
        for (int i = 2; i <= n; i++) {
            noOfPFac[i] = noOfPFac[i / spm[i]] + 1;
        }
    }
};


int main() {
    int SIZE = 10;
    Sieve s(SIZE);
    deb(s.sieve);
    deb(s.spm);
    deb(s.noOfPFac);
    deb(s.sumOfPFac);
}

/*
    Output:
    idx          = 0 1 2 3 4 5 6 7 8 9 10
    s.sieve      = 0 0 1 1 0 1 0 1 0 0  0 
    s.spm        = 0 0 2 3 2 5 2 7 2 3  2 
    s.noOfPFac   = 0 0 1 1 2 1 2 1 3 2  2 
    s.sumOfPFac  = 0 0 2 3 2 5 5 7 2 3  7 
*/