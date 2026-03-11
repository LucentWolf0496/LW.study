x , y = map(int , input().split())
sum = 0
while x <= y:
    if x % 17 == 0:
        sum += x
    x += 1
print(sum)