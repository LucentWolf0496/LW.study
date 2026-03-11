a , x , y = map(str , input().split(','))
s1 = []
s2 = []
len0 = len(a)
len1 = len(x)
len2 = len(y)
for i in range (0 , len0 - len1 + 1):
    sub = a[i : i + len1]
    if (sub == x):
        s1.append(i)
for i in range (0 , len0 - len2 + 1):
    sub = a[i : i + len2]
    if (sub == y):
        s2.append(i)
if s1 and s2 and s1[0] + len1 - 1 < s2[len(s2) - 1]:
    print(s2[len(s2) - 1]-s1[0]-len1)
else:
    print(-1)