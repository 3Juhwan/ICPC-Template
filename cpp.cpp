#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;


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


/*     Compress     */

vector<ll> i_pos, j_pos;
vector<p> v;

void compress(){
	sort(i_pos.begin(), i_pos.end());
	i_pos.erase(unique(i_pos.begin(), i_pos.end()), i_pos.end());
	sort(j_pos.begin(), j_pos.end());
	j_pos.erase(unique(j_pos.begin(), j_pos.end()), j_pos.end());
	for (int i = 0; i < v.size(); i++){
		v[i].x = lower_bound(i_pos.begin(), i_pos.end(), v[i].x) - i_pos.begin();
		v[i].y = lower_bound(j_pos.begin(), j_pos.end(), v[i].y) - j_pos.begin();
	}
}


/*     Main     */

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
}