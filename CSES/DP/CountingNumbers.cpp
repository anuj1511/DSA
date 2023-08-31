// Author: Anuj Jadhav
// https://www.youtube.com/watch?v=dQw4w9WgXcQ

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long 
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
#define deb(x) cerr << #x <<" = "; _print(x); cerr << endl;
#define deb2(x, y) cerr << #x << " = "; _print(x); cerr << ", " << #y << " = "; _print(y); cerr << endl;
#define deb3(x, y, z) _print(x); cerr << " "; _print(y); cerr << " "; _print(z); cerr << endl;
#define deb4(a, b, c, d) _print(a); cerr << " "; _print(b); cerr << " "; _print(c); cerr << " "; _print(d); cerr << endl;
#define deb5(a, b, c, d, e) _print(a); cerr << " "; _print(b); cerr << " "; _print(c); cerr << " "; _print(d); cerr << " "; _print(e); cerr << endl;
#else
#define deb(x)
#define deb2(x, y)
#define deb3(x, y, z)
#define deb4(a, b, c, d)
#define deb5(a, b, c, d, e)
#endif

void _print(int x) { cerr << x; }
void _print(char x) { cerr << x; }
void _print(string x) { cerr << x; }
void _print(double x) { cerr << x; }
void _print(ull x) { cerr << x; }
void _print(lld x) { cerr << x; }

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);

template <class T, class V> void _print(pair <T, V> p) { cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}"; }
template <class T> void _print(vector <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(set <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(multiset <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print(map <T, V> v) { cerr << "[ "; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print(unordered_map <T, V> v) { cerr << "[ "; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }

using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//order_of_key(k) : number of elements strictly lesser than k
//find_by_order(k-1): It returns to an iterator to the kth element.Use for deleting in multiset

int dp[19][2][2][2][10];

int helper(int i, string& low, string& high, 
	bool tight_upper, bool tight_lower, bool zero_start, int prev) {
	int n = low.size();
	if(i == n) return 1;

	if(dp[i][tight_upper][tight_lower][zero_start][prev] != -1) return dp[i][tight_upper][tight_lower][zero_start][prev];

	int st = tight_lower ? low[i] - '0' : 0;
	int end = tight_upper ? high[i] - '0' : 9;

	int res = 0;
	for(int ch = st; ch <= end; ch++) {
		bool new_tight_upper = tight_upper & ch == end;
		bool new_tight_lower = tight_lower & ch == st;
		bool new_zero_start = zero_start & ch == 0;

		if(ch == prev) {
			if(ch == 0 && new_zero_start) {
				// allow
			} else continue;
		}

		int val = helper(i+1, low, high, new_tight_upper, new_tight_lower, new_zero_start, ch);
		res += val;
	}
	return dp[i][tight_upper][tight_lower][zero_start][prev] = res;
}

void solution() {
	memset(dp, -1, sizeof(dp));
	string low, high; cin >> low >> high;
	low = string(high.size() - low.size(), '0') + low;
	int res = helper(0, low, high, true, true, true, 0);
	cout << res << endl;
}

int32_t main() {
	// #ifndef ONLINE_JUDGE
	//	 freopen("Error.txt", "w", stderr);
	// #endif
	fastio();

	int test = 1;

	while (test--) {
		solution();
	}

	return 0;
}