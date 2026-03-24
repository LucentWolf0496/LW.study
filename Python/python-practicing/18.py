n = int(input())
table = []
countx = []
county = []
for i in range (0 , n):
    row = list(map(int , input().split()))
    table.append(row)
for i in range (0 , n):
    for j in range (0 , n):
        if table[i][j] == 0:
            countx.append(i)
            county.append(j)
p = countx[len(countx) - 1] - countx[0] - 1
q = county[len(county) - 1] - county[0] - 1
ans = p * q
if ans <= 0:
    print(0)
else:
    print(ans)