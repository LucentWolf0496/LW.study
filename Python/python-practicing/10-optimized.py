n, m = map(int, input().split())
lights = [1] * (n + 1)  # 1 表示开，0 表示关，初始全开

for i in range(1, m + 1):
    for j in range(i, n + 1, i):  # 从 i 开始，每次加 i
        lights[j] = 1 - lights[j]  # 切换状态

# 收集关闭的灯（状态为 0）
closed = [str(i) for i in range(1, n + 1) if lights[i] == 0]

# 用逗号连接并输出
print(','.join(closed))