person = {"name": "Alice", "age": 25}
print(person["name"])            # 访问
person["age"] = 26               # 修改
person["city"] = "New York"      # 添加新键值对

# 遍历
for key, value in person.items():
    print(key, value)

# 检查键是否存在
if "name" in person:
    print("name exists")
if "wolf" in person:
    print("woof!!!")
else:
    print("meow!!!")

s1 = {1, 2, 3}
s2 = {3, 4, 5}
print(s1 | s2)   # {1,2,3,4,5}
print(s1 & s2)   # {3}
s1.add(6)
s1.remove(2)
print(s1 | s2)   # {1,3,4,5,6}
print(s1 & s2)   # {3}

print("Hello", "World", sep=", ", end="!\n")   # Hello, World!
print("Hello", "World")   # HelloWorld
print("HeLinWorld")   # ?frh:@#:{}1;]]2rj9