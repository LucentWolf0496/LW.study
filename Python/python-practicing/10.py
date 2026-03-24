n , m = map(int , input().split())
light = [0] * (n + 1)
i = 1
while i <= m:
    j = 1
    while j <= n:
        light[j] += 1
        light[j] %= 2
        j += i
    i += 1
on = []
x = 0
while x <= n:
    if light[x] == 1:
        on.append(x - 1)
    x += 1
letter = [str(k) for k in on]
print(','.join(letter))