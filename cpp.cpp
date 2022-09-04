#include <bits/stdc++.h>
using namespace std;
#define FAST ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define all(v) v.begin(), v.end()
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9+7;
const int MOD = 1e9+7;
const int MAX = 101010;


/*     Segment Tree     */

const int sz = 80000;
ll tree[sz << 1];

void init() {
    for(int i=sz-1; i>0; --i) {
        tree[i] = tree[i << 1] + tree[i << 1|1];
    }
}

void update(int idx, ll val) {
    tree[sz + idx] = val;
    for(int i=(sz+idx) >> 1; i > 0; i >>= 1) {
        tree[i] = tree[i << 1] + tree[i << 1|1];
    }
}

ll sum(int left, int right) {
    ll ret = 0;
    for(int l=left+sz, r=right+sz; l<=r; l>>=1, r>>=1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }
    return ret;
}


/* Segment Tree with lazy propagation */

const int sz = 1e6+10;

ll tree[sz*4];
ll lazy[sz*4];

void update_lazy(int x, int s, int e) {
	if (lazy[x] != 0) {
		tree[x] += (e - s + 1)*lazy[x];
		if (s != e) {
			lazy[x << 1] += lazy[x];
			lazy[(x << 1) + 1] += lazy[x];
		}
		lazy[x] = 0;
	}
}

void update_range(int x, int s, int e, int l, int r, ll diff) {
	update_lazy(x, s, e);
	if (e < l || s > r) return;
	if (s >= l && e <= r) {
		tree[x] += (e - s + 1)*diff;
		if (s != e) {
			lazy[x << 1] += diff;
			lazy[(x << 1) + 1] += diff;
		}
		return;
	}
	update_range(x << 1, s, (s + e) / 2, l, r, diff);
	update_range((x << 1) + 1, (s + e) / 2 + 1, e, l, r, diff);
	tree[x] = tree[x << 1] + tree[(x << 1) + 1];
}

ll get(int x, int s, int e, int l, int r) {
	update_lazy(x, s, e);
	if (s > r || e < l) return 0;
	if (s >= l && e <= r) return tree[x];
	return get(x * 2, s, (s + e) / 2, l, r) + get(x * 2 + 1, (s + e) / 2 + 1, e, l, r);
}


/*     Merge Sort Tree     */

int n, k, arr[MAX];
const int sz = 1 << 17; 	// should be power of 2 (2^n)
vector<int> tree[sz << 1];

void add(int x, int v) {
    x |= sz; tree[x].push_back(v);
}

void build() {
    for (int i=1; i<=n; i++) add(i, arr[i]);
    for (int i=sz-1; i; i--) {
        tree[i].resize(tree[i*2].size() + tree[i*2+1].size());
        merge(all(tree[i*2]), all(tree[i*2+1]), tree[i].begin());
    }
}

int query(int l, int r, int k) {
    l |= sz, r |= sz;
    int ret = 0;
    while (l <= r) {
        if (l & 1) ret += tree[l].end() - upper_bound(all(tree[l]), k), l++;
        if (~r & 1) ret += tree[r].end() - upper_bound(all(tree[r]), k), r--;
        l >>= 1, r >>= 1;
    }
    return ret;
}


/*     Compress     */

// 1 Dimension

// vector<int> arr(n);
// for (auto &x: arr) cin >> x;
vector<int> tmp(all(arr));
sort(all(tmp)); tmp.erase(unique(all(tmp)), tmp.end());
for (int& x: arr) x = lower_bound(all(tmp), x) - tmp.begin();


/*     CCW     */

pll a, b, c, d;

ll ccw(pll a, pll b, pll c) {
    ll ret = a.first*b.second+b.first*c.second+c.first*a.second-(b.first*a.second+c.first*b.second+a.first*c.second);
    return ret;
    // Use below when you use isCross 
    // if (ret > 0) return 1;
    // if (ret == 0) return 0;
    // return -1;
}

int isCross(pll a, pll b, pll c, pll d) {
    if (ccw(a, b, c) * ccw(a, b, d) == 0 && ccw(c, d, a) * ccw(c, d, b) == 0) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        if (a <= d && c <= b) return 1;
        return 0;
    }
    if (ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0) return 1;
    return 0;
}


/*     Main     */

void solve() {
	
}

int main()
{
    FAST;
	solve();
}