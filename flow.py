length = n # 정점 개수

graph = [[] for _ in range(length)]
capacity = [[0 for _ in range(length)] for _ in range(length)]
flow = [[0 for _ in range(length)] for _ in range(length)]

start = n - 1 # 시작 정점
end = n - 2 # 종료 정점

# 그래프 모델링

# BFS 로 흘릴 수 있는 유량 경로 찾기
def bfs(s, e, vis):
    queue = deque()
    queue.append(s)

    while queue:
        now_node = queue.popleft()
        if now_node == e: return True
        for next_node in graph[now_node]:
            # 용량이 남거나 역간선이 활성화되고, 방문하지 않은 정점
            if capacity[now_node][next_node] - flow[now_node][next_node] > 0 and vis[next_node] == -1:
                vis[next_node] = now_node
                queue.append(next_node)
    return False

# 최대 유량
def solve(s, e):
    answer = 0
    while True:
        visited = [-1 for _ in range(length)]
        if not bfs(s, e, visited): return answer

        min_flow = INF
        now = e
        while now != s:
            go = visited[now]
            min_flow = min(min_flow, capacity[go][now] - flow[go][now])
            now = go

        now = e
        while now != s:
            go = visited[now]
            flow[go][now] += min_flow
            flow[now][go] -= min_flow
            now = go

        answer += min_flow
