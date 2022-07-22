"""     Input     """
import sys
input = lambda : sys.stdin.readline().rstrip()
"""     Exponentiation By Squaring     """
MOD = 1_000_000_007
def fexp(a, b):
    ret = 1
    while b:
        if b & 1:
            ret *= a
            ret %= MOD
        a *= a
        a %= MOD
        b >>= 1
    return ret
"""     Combinatorics     """
MOD = 1_000_000_007
SIZE = 300001
# Factorial 
fac, invfac = [0] * SIZE, [0] * SIZE
def precompute():
    fac[0] = 1
    for i in range(1, SIZE):
        fac[i] = fac[i-1] * i % MOD
    # for i in range(SIZE):
        # invfac[i] = fexp(fac[i], MOD - 2)
precompute()
# Combination
def combination_all(n, k):
    ret = fac[n] * invfac[k] % MOD
    return ret * invfac[n - k] % MOD
def combination_indiv(n, k):
    x = fac[k] * fac[n-k] % MOD
    return fac[n]*fexp(x, MOD-2)%MOD
# Catalan
def catalan(n):
    ret = fac[2*n] * invfac[n+1] % MOD
    return ret * invfac[n] % MOD
"""     Tree     """
# Segment Tree
treeSize = 1 << 20
tree = [0] * (treeSize << 1)
def init():
    for i in range(treeSize-1, 0, -1):
        tree[i] = tree[i<<1] + tree[i<<1|1]
def update(idx, val):
    tree[treeSize+idx] = val;
    i = (treeSize+idx) >> 1
    while i > 0:        
        tree[i] = tree[i<<1] + tree[i<<1|1]
        i >>= 1
def sum(left, right):
    ret = 0
    l, r = left+treeSize, right+treeSize
    while l <= r:
        if l & 1:
            ret += tree[l]
            l += 1
        if ~r & 1:
            ret += tree[r]
            r -= 1
        l >>= 1
        r >>= 1
    return ret
# [2042] 구간 합 구하기
# https://www.acmicpc.net/problem/2042
n, m, k = map(int, input().split())
for i in range(n):
    tree[treeSize + i] = int(input())
init()
for __ in range(m+k):
    a, b, c = map(int, input().split())
    if a==1:
        update(b-1, c)
    else:
        print(sum(b-1, c-1))
"""     Number Theory     """
# Sieve of Eratosthenes
SIZE = 10_000_001
prime = [1] * SIZE
prime[0], prime[1] = 0, 0
for i in range(2, int(SIZE**0.5)+1):
    if prime[i]:
        for j in range(i*2, SIZE, i):
            prime[j] = 0
"""     Array Rotate     """
arr = [[1, 2], [3, 4], [5, 6]]
# Clock-Wise-Rotate
rotated = list(zip(*arr[::-1]))
# [(5, 3, 1), (6, 4, 2)]
# Transposition
rotated = list(zip(*arr))
# [(1, 3, 5), (2, 4, 6)]
"""     Trie     """
class Node(object):
    def __init__(self, key, data=None):
        self.key = key
        self.data = data
        self.child = {}
class Trie(object):
    def __init__(self):
        self.head = Node(None)
    def insert(self, s):
        curr = self.head
        for c in s:
            if c not in curr.child:
                curr.child[c] = Node(c)
            curr = curr.child[c]
        curr.data = s
    def search(self, s):
        curr = self.head
        for c in s:
            if c in curr.child:
                curr = curr.child[c]
            else:
                return False
        if curr.data != None:
            return True
"""     KMP     """
def get_pi(p):
    n = len(p)
    pi = [0]*n
    j = 0
    for i in range(1, n):
        while j > 0 and p[i] != p[j]:
            j = pi[j-1]
        if p[i] == p[j]:
            pi[i] = j+1
            j += 1
    return pi
def kmp(s, p):
    ans = []
    n, m = len(s), len(p)
    pi = get_pi(p)
    j = 0
    for i in range(n):
        while j > 0 and s[i] != p[j]:
            j = pi[j-1]
        if s[i] == p[j]:
            if j == m-1:
                ans.append(i-m+1);
                j = pi[j];
            else:
                j += 1
    return ans