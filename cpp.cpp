#include<bits/stdc++.h>
using namespace std;
#define FAST ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define INF 1e9+7
#define MOD 1e9+7


/*     Segment Tree     */

const int treeSize = 80000;
ll tree[treeSize << 1];

void init()
{
    for(int i=treeSize-1; i>0; --i) {
        tree[i] = tree[i << 1] + tree[i << 1|1];
    }
}

void update(int idx, ll val) {
    tree[treeSize + idx] = val;
    for(int i=(treeSize+idx) >> 1; i > 0; i >>= 1) {
        tree[i] = tree[i << 1] + tree[i << 1|1];
    }
}

ll sum(int left, int right) {
    ll ret = 0;
    for(int l=left+treeSize, r=right+treeSize; l<=r; l>>=1, r>>=1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }
    return ret;
}


/* Segment Tree with lazy propagation */

const int treeSize = 1e6+10;

ll tree[treeSize*4];
ll lazy[treeSize*4];

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


/*     Compress     */

vector<ll> i_pos, j_pos;
vector<pair<ll, ll>> v;

void compress(){
	sort(i_pos.begin(), i_pos.end());
	i_pos.erase(unique(i_pos.begin(), i_pos.end()), i_pos.end());
	sort(j_pos.begin(), j_pos.end());
	j_pos.erase(unique(j_pos.begin(), j_pos.end()), j_pos.end());
	for (int i = 0; i < v.size(); i++){
		v[i].first = lower_bound(i_pos.begin(), i_pos.end(), v[i].first) - i_pos.begin();
		v[i].second = lower_bound(j_pos.begin(), j_pos.end(), v[i].second) - j_pos.begin();
	}
}


/*     Main     */

void solve() {
	
}

int main()
{
    FAST;
	solve();
}