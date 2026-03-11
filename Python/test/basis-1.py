a = 42          # int
b = 3.14        # float
c = True        # bool
d = "Hello"     # str
e = 1 + 2j      # complex

print(type(a))      # <class 'int'>
s = "123"
print(type(s))
n = int(s) + 10     # 转换为整数再运算
print(n)

s = "Python"
print(s[0])       # P
print(s[-1])      # n
print(s[1:4])     # yth
print(len(s))     # 6
print(s.upper())  # PYTHON
print(s[::2])     # Pto

x = 10
if x > 0:
    print("positive")
elif x == 0:
    print("zero")
else:
    print("negative")