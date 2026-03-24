def can_reach(maze, r, c, N):
    # 到达终点
    if r == N - 1 and c == N - 1:
        return True
    # 尝试向右走
    if c + 1 < N and maze[r][c + 1] == 0:
        if can_reach(maze, r, c + 1, N):
            return True
    # 尝试向下走
    if r + 1 < N and maze[r + 1][c] == 0:
        if can_reach(maze, r + 1, c, N):
            return True
    return False

# 读取输入
N = int(input().strip())
maze = []
for _ in range(N):
    row = list(map(int, input().strip().split()))
    maze.append(row)

# 从起点开始判断
if can_reach(maze, 0, 0, N):
    print("Yes")
else:
    print("No")