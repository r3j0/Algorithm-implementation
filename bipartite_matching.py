selected = [-1 for _ in range(n)] # 선택된 B
visited = [0 for _ in range(n)] # 선택된 A

def bimatch(now):
  if visited[now] == 1: return False
  visited[now] = 1
  
  for go in graph[now]:
    if selected[go] == -1 or bimatch(selected[go]):
      selected[go] = now
      return True
  return False
  
res = 0
for i in range(n):
  visited = [0 for _ in range(n)]
  if bimatch(i): res += 1
print(res)
