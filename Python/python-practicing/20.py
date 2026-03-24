def get(x , y):
    if x > 100000:
        return False
    if x == y:
        return True
    if get(x * 2 + 1 , y):
        return True
    if get(x * 3 + 1 , y):
        return True

k , x = map(int , input().split(','))# 简单的递归，注意输入格式解析
if get(k , x):
    print("YES")
else:
    print("NO")