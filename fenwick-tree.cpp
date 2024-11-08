// #include <bits/stdc++.h>
// #define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
// using ll = long long;

template<size_t sz>
struct FenwickTree {
  vector<ll> tree;
  FenwickTree() : tree(sz) {}
  void update(ll idx, ll val) {
    for (; idx <= sz; idx += idx & -idx) tree[idx] += val;
  }
  ll sums(ll idx) {
    if (idx < 1) return 0;
    if (idx > sz) idx = sz;
    ll ret = 0;
    for (; idx; idx -= idx & -idx) ret += tree[idx];
    return ret;
  }
};

FenwickTree<MAX-1> ft;
