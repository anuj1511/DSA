// Author: Anuj Jadhav
// https://www.youtube.com/watch?v=dQw4w9WgXcQ

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MOD 1000000007
#define MOD1 998244353
#define PI 3.141592653589793238462
#define INF 1e18

#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second

#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) x.rbegin(), x.rend()
#define ub upper_bound
#define lb lower_bound
#define bsrch binary_search
#define mine *min_element
#define maxe *max_element
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) ((a * b) / gcd(a, b))
#define rep(i, n) for(long long i = 0; i < n; i++)

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#ifndef ONLINE_JUDGE
#define deb(x) cout << #x <<" = "; _print(x); cout << endl;
#define deb2(x, y) cout << #x << " = "; _print(x); cout << ", " << #y << " = "; _print(y); cout << endl;
#define deb3(x, y, z) _print(x); cout << " "; _print(y); cout << " "; _print(z); cout << endl;
#define deb4(a, b, c, d) _print(a); cout << " "; _print(b); cout << " "; _print(c); cout << " "; _print(d); cout << endl;
#define deb5(a, b, c, d, e) _print(a); cout << " "; _print(b); cout << " "; _print(c); cout << " "; _print(d); cout << " "; _print(e); cout << endl;
#else
#define deb(x)
#define deb2(x, y)
#define deb3(x, y, z)
#define deb4(a, b, c, d)
#define deb5(a, b, c, d, e)
#endif

void _print(int x) { cout << x; }
void _print(char x) { cout << x; }
void _print(string x) { cout << x; }
void _print(double x) { cout << x; }
void _print(ull x) { cout << x; }
void _print(lld x) { cout << x; }

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);

template <class T, class V> void _print(pair <T, V> p) { cout << "{"; _print(p.ff); cout << ","; _print(p.ss); cout << "}"; }
template <class T> void _print(vector <T> v) { cout << "[ "; for (T i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T> void _print(set <T> v) { cout << "[ "; for (T i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T> void _print(multiset <T> v) { cout << "[ "; for (T i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T, class V> void _print(map <T, V> v) { cout << "[ "; for (auto i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T, class V> void _print(unordered_map <T, V> v) { cout << "[ "; for (auto i : v) { _print(i); cout << " "; } cout << "]"; }

using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//order_of_key(k) : number of elements strictly lesser than k
//find_by_order(k-1): It returns to an iterator to the kth element.Use for deleting in multiset
