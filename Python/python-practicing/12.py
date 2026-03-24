# 该题实现空心的关键在于用数组条件下的append来构建每一行的内容，防止print自动换行处理导致错误
# 读取输入
params = input().split()
h = int(params[0])          # 高
w = int(params[1])          # 宽
ch = params[2]              # 填充字符
solid = int(params[3])      # 1=实心，0=空心

for i in range(h):
    row = []
    for j in range(w):
        if solid == 1:                      # 实心：全填符号
            row.append(ch)
        else:                               # 空心
            if i == 0 or i == h-1 or j == 0 or j == w-1:
                row.append(ch)              # 边界填符号
            else:
                row.append(' ')              # 内部填空格
    print(''.join(row))