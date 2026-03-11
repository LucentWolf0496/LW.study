def item(x , y):
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
    ac = (i - 1) % a
    bc = (i - 1) % b
    acount += item(lista[ac] , listb[bc])

if (acount > 0):
    print('A')
elif (acount < 0):
    print('B')
else:
    print("draw")