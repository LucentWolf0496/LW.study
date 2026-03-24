import math # import的引入包类似cpp中的#include
print(math.sqrt(16))

from random import randint
print(randint(1, 10))
print(math.sqrt(randint(1,1000)))

# 列表推导式————简洁地创建列表。
squares = [x**2 for x in range(10)]          # [0,1,4,9,...,81]
evens = [x for x in range(20) if x % 2 == 0] # 带条件
print(squares[5])
print(evens[4])

# 三元表达式
age = 20
status = "adult" if age >= 18 else "minor"
print(status)

# 枚举————enumerate在遍历时同时获取索引和值。
fruits = ["apple", "banana", "cherry"]
for i, fruit in enumerate(fruits):
    print(i, fruit)

# 解包（Unpacking）将可迭代对象中的元素赋值给多个变量。
a, b, c = [1, 2, 3]
first, *rest = [1, 2, 3, 4]   # first=1, rest=[2,3,4]
print(a , b , c , first , rest[2] , rest)

# zip 函数————并行迭代多个可迭代对象。
names = ["Alice", "Bob", "Charlie"]
ages = [25, 30, 35]
for name, age in zip(names, ages):
    print(name, age)