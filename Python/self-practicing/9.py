n = int(input())
num = list(map(int , input().strip().split()))
count = 0
for i in num:
    a = i // 1000
    i %= 1000
    b = i // 100
    i %= 100
    c = i // 10
    i %= 10
    d = i
    if d - a - b - c > 0:
        count += 1
print(count)
for i in num:
    print(i)