def dfs(u, graph, visited):
    visited[u] = True
    # 处理节点 u ...
    for v in graph[u]:
        if not visited[v]:
            dfs(v, graph, visited)