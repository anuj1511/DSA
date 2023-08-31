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

int my_lower_bound(int st, vector<vector<int>>& arr, int key) {
	int end = arr.size() - 1;
	while(st <= end) {
		int mid = st + (end - st) / 2;
		if(arr[mid][0] > key) end = mid - 1;
		else st = mid + 1;
	}
	return st;
}

void solution() {
	int n; cin >> n;
	vector<vector<int>> arr;
	for(int i = 0; i < n; i++) {
		int st, end, profit; cin >> st >> end >> profit;
		arr.push_back({st, end, profit});
	}

	sort(arr.begin(), arr.end());
	deb(arr);
	vector<int> dp(n, 0);
	dp[n-1] = arr[n-1][2];

	for(int i = n-2; i >= 0; i--) {
		int st = arr[i][0], end = arr[i][1], profit = arr[i][2];
		int j = my_lower_bound(i+1, arr, end);
		int pick = profit + ((j != n) ? dp[j] : 0);
		int notPick = dp[i+1];
		dp[i] = max(pick, notPick);
	}

	cout << dp[0] << endl;
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