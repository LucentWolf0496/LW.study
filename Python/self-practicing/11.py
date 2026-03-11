item = 1
sum = 0
n = int(input())
for i in range (1 , n + 1):
    sum += item
    item *= i + 1
print(sum)