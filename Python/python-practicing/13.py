num = list(map(int , input().strip().split()))
n = num[0]
check = [0] * n
meow = 0
for i in range(1 , n):
    if abs(num[i] - num[i + 1]) >= n:# python也要注意处理数组越界啊！！
        meow = 1
    else:
        if check[abs(num[i] - num[i + 1])] == 0:
            check[abs(num[i] - num[i + 1])] += 1
        else:
            meow = 1
if meow == 1:
    print("Not jolly")
else:
    print("Jolly")