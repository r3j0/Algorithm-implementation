#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAX 100001
using namespace std;

int n, m, sqrtN;
int arr[MAX];

struct Query {
  int i, s, e;
};

Query q[MAX];
int cnt[1000001];
int answer[MAX];

bool cmp(Query a, Query b) {
  if (a.s / sqrtN != b.s / sqrtN) return a.s < b.s;
  return a.e < b.e;
}

int main(void) {
  fastio;

  cin >> n;
  sqrtN = sqrt(n);
  for (int i = 1; i <= n; i++) cin >> arr[i];

  cin >> m;
  for (int idx = 0; idx < m; idx++) {
    cin >> q[idx].s >> q[idx].e;
    q[idx].i = idx;
  }

  sort(q, q+m, cmp);
  int now = 0;

  for (int i = q[0].s; i <= q[0].e; i++) {
    if (cnt[arr[i]] == 0) now += 1;
    cnt[arr[i]] += 1;
  }

  answer[q[0].i] = now;
  for (int i = 1; i < m; i++) {
    for (int j = q[i-1].s; j < q[i].s; j++) {
      cnt[arr[j]] -= 1;
      if (cnt[arr[j]] == 0) now -= 1;
    }
    for (int j = q[i-1].e; j > q[i].e; j--) {
      cnt[arr[j]] -= 1;
      if (cnt[arr[j]] == 0) now -= 1;
    }
    for (int j = q[i-1].s - 1; j >= q[i].s; j--) {
      if (cnt[arr[j]] == 0) now += 1;
      cnt[arr[j]] += 1;
    }
    for (int j = q[i-1].e + 1; j <= q[i].e; j++) {
      if (cnt[arr[j]] == 0) now += 1;
      cnt[arr[j]] += 1;
    }

    answer[q[i].i] = now;
  }

  for (int i = 0; i < m; i++) cout << answer[i] << "\n";
  return 0;
}
