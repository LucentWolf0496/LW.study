n , x , y = map(int , input().split())
eaten = 0
if y % x == 0:
    eaten = y // x
else:
    eaten = y // x + 1
if n - eaten >= 0:
    print(n - eaten)
else:
    print(0)