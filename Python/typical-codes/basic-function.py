def item(x , y):# 初步使用python函数
    if (x == y):
        return 0
    elif(x == 0 and y == 2) or (x == 2 and y == 5) or (x == 5 and y == 0):
        return 1
    else:
        return -1

x , a , b = map(int , input().split())
lista = list(map(int , input().split()))
listb = list(map(int , input().split()))
acount = 0
for i in range(1 , x + 1):
    ac = (i - 1) % a # 注意数组索引！！
    bc = (i - 1) % b # 注意数组索引！！
    acount += item(lista[ac] , listb[bc])

if (acount > 0):
    print('A')
elif (acount < 0):
    print('B')
else:
    print("draw")