// Problem
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#define MAX 4000003
#define INF 2000000000
using namespace std;
using ll = long long;

int n;

struct Edge {
  int next;
  ll capacity, cost, flow;
  Edge* rev;
  Edge(int _next, ll _capacity, ll _cost) : next(_next), capacity(_capacity), cost(_cost), flow(0), rev(nullptr) {}

  void updateFlow(ll f) {
    flow += f;
    rev->flow -= f;
  }
  ll remainFlow() { return (capacity - flow); }
};
vector<vector<Edge*>> graph;

void addEdge(int s, int e, ll cap, ll cos) {
  graph[s].push_back(new Edge(e, cap, cos));
  graph[e].push_back(new Edge(s, 0, -cos));
  graph[s].back()->rev = graph[e].back();
  graph[e].back()->rev = graph[s].back();
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;

  int start = MAX-2;
  int end = MAX-1;
  int length = MAX;
  graph.assign(length, vector<Edge*>());

  // 그래프 모델링 
  // addEdge(start, firstK, k, 0);
  // addEdge(firstK, a.second.first, 1, -arr[a.second.first/n][a.second.first%n]);

  vector<int> pre;
  vector<ll> dist;
  vector<bool> inQueue;
  vector<Edge*> path;
  
  pre.assign(length, -1);
  dist.assign(length, INF);
  inQueue.assign(length, false);
  path.assign(length, nullptr);
  
  ll answer = 0;
  
  while (1) {
    fill(pre.begin(), pre.end(), -1);
    fill(dist.begin(), dist.end(), INF);
    fill(inQueue.begin(), inQueue.end(), false);
    fill(path.begin(), path.end(), nullptr);
  
    dist[start] = 0;
    inQueue[start] = true;
  
    queue<int> q;
    q.push(start);
  
    while (!q.empty()) {
      int now = q.front(); 
      q.pop();
      inQueue[now] = false;
    
      for (Edge* e : graph[now]) {
        if (e->remainFlow() > 0 && dist[e->next] > dist[now] + e->cost) {
          dist[e->next] = dist[now] + e->cost;
          pre[e->next] = now;
          path[e->next] = e;
      
          if (inQueue[e->next] == false) {
            inQueue[e->next] = true;
            q.push(e->next);
          }
        }
      }
    }
    
    if (pre[end] == -1) break;
  
    ll flow = INF;
    for (int bt = end; bt != start; bt = pre[bt]) { 
      flow = min(flow, path[bt]->remainFlow()); 
    }
  
    for (int bt = end; bt != start; bt = pre[bt]) { 
      path[bt]->updateFlow(flow);
      answer += path[bt]->cost;
    }
  }

  cout << answer;
  return 0;
}
