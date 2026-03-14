n = int(input())
x = 2
y = 1
sum = 0
for i in range (0 , n):
    sum += x / y
    z = x
    x = x + y
    y = z
print("%.4f" % sum)