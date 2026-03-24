n , m = map(int , input().split())
x = []
for i in range (0 , n):
    row = list(map(int , input().split()))
    x.append(row)
for i in range (0 , n):
    row = list(map(int , input().split()))
    temp = []# python数组————常常使用空数组+append完成，数组其实可加工，但是字符串不可加工
    for j in range (0 , m):
        temp.append(row[j] + x[i][j])
    print(' '.join(map(str , temp)))# 转化变量类型之后可以使用join函数链接数组元素输出

# 下面是简化的写法练习，试着去感受python的简洁特性：
n, m = map(int, input().split())
A = [list(map(int, input().split())) for _ in range(n)]
B = [list(map(int, input().split())) for _ in range(n)]
for i in range(n):
    print(' '.join(str(A[i][j] + B[i][j]) for j in range(m)))