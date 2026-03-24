def swap(x, y):
    return y, x           # 返回元组

a, b = swap(10, 20)       # a=20, b=10
print(a , b , a + b , a ** b , a / b , b // a) # a / b is type "float"

def modify_list(lst):
    lst.append(4)         # 会影响原列表

my_list = [1, 2, 3]
modify_list(my_list)
print(my_list)            # [1, 2, 3, 4]

fruits = ["apple", "banana", "cherry"]
fruits.append("orange")          # 末尾添加
fruits.insert(1, "grape")        # 在索引 1 处插入
fruits.remove("banana")          # 删除第一个匹配项
last = fruits.pop()              # 弹出最后一个元素
print(len(fruits))               # 长度
for i in fruits:
    print(i)

point = (10, 20, 20230831, 5555555)
x, y, zzz, sleep = point                     # 解包
print (x , y , zzz , sleep)