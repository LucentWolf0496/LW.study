# 在 Python 中：
# 小括号 () 表示元组（tuple），是不可变序列，例如 (1, 2, 3)。
# 中括号 [] 表示列表（list），是可变序列，例如 [1, 2, 3]。使用append语句来加入元素
# 大括号 {} 有两种用途：
# 字典（dict）：键值对集合，例如 {'a': 1, 'b': 2}。
# 集合（set）：无序不重复元素集，例如 {1, 2, 3}。使用add语句来加入元素
# 注意：空的大括号 {} 表示空字典，空集合必须用 set() 创建。
# 所以，set 使用的是大括号 {}，而不是小括号。小括号是元组的标志。
n = int(input())
table = []# 储存本题目人际关系信息的二维数组table
count = [0] * 101
for i in range (0 , n):
    row = list(map(int , input().split()))
    ans = []
    ans.append(row[0])
    ans.append(row[1])
    s = row[1]
    for j in range (0 , s):
        count[row[2 + j]] += 1# 注意索引加工
        ans.append(row[2 + j])
    table.append(ans)
max = 0
maxNum = 0
for i in range(1 , 101):
    if (count[i] > max):
        max = count[i]
        maxNum = i
print(maxNum)# 题目保证maxNum只有一个
result1 = set()# 使用set类型去重哈希数组从而避免重复，set应该用add而不使append
for i in range (0 , n):
    for j in range (0 , table[i][1]):
        if (table[i][j + 2] == maxNum):
            result1.add(table[i][0])
result = sorted(result1)# set排序代码sorted()
print(' '.join(map(str , result)))# 强制转换类型便于输出正确格式