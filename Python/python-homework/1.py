cipher = input().strip()
n = len(cipher)
ans = [''] * n

# 递归填充原始字符串
def dfs(start, length, idx):
    """返回处理完当前子树后的密文索引"""
    if length == 0:
        return idx
    mid = start + (length - 1) // 2   # 中轴在原始字符串中的位置
    ans[mid] = cipher[idx]           # 当前密文字符即为中轴字符
    idx += 1
    left_len = (length - 1) // 2
    right_len = length - 1 - left_len
    idx = dfs(start, left_len, idx)       # 处理左半部分
    idx = dfs(mid + 1, right_len, idx)    # 处理右半部分
    return idx

dfs(0, n, 0)
print(''.join(ans))