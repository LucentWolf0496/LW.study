s = input()
n = len(s)
max1 = 0
temp = 1
item = 'a'
tempitem = 'a'
for i in range (0 , n - 1):
    tempitem = s[i]
    if s[i + 1] == tempitem:
        temp += 1
    else:
        if (temp > max1):
            max1 = temp
            item = tempitem
            temp = 1
        else:
            temp = 1
if temp > max1:# 勿漏最后的比较
    max1 = temp
    item = tempitem
print(item , max1)