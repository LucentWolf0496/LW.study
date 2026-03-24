name = input("Enter your name: ")
age = int(input("Enter your age: "))
# 输入：input()
# 从标准输入读取一行，返回字符串（可包含换行符）。
# 如果需要数字，需手动转换。
print (name , age)
print(f"My name is {name} and I am {age} years old.")

with open("data.txt", "w") as f:
    f.write("Hello, world!\n")
    f.writelines(["line1\n", "line2\n"])

with open("data.txt", "r") as f:
    content = f.read()
    print(content)

with open("data.txt", "r") as f:
    for line in f:          # 逐行迭代
        print(line.strip())

# 使用 open(filename, mode)，返回文件对象。
# 模式：'r' 读（默认），'w' 写（覆盖），'a' 追加，'b' 二进制模式，'+' 读写。
# 推荐使用 with 语句自动关闭文件。