from collections import deque

def bfs(start, graph, visited):
    queue = deque([start])
    visited[start] = True

    while queue:
        u = queue.popleft()
        # 处理节点 u ...
        for v in graph[u]:
            if not visited[v]:
                visited[v] = True
                queue.append(v)