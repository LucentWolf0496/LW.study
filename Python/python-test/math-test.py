# 作为Python的标准库，math 最大的优点就是无需安装，直接导入即可使用。它提供了大量基础的数学函数和常量。
import math

# 常量
print(math.pi)        # 圆周率 3.141592653589793
print(math.e)        # 自然常数 2.718281828459045

# 基础运算
print(math.sqrt(16))  # 平方根: 4.0
print(math.factorial(5)) # 阶乘: 120
print(math.gcd(20, 8))   # 最大公约数: 4

# 幂指对函数
print(math.pow(2, 3)) # 2的3次方: 8.0 (返回浮点数)
print(math.exp(2))    # e的2次方: 7.389...
print(math.log(100, 10)) # 以10为底100的对数: 2.0

# 三角函数 (角度用弧度制表示)
angle = math.pi / 2   # 90度
print(math.sin(angle)) # 正弦: 1.0

# 取整函数
x = 3.6
print(math.ceil(x))   # 向上取整: 4
print(math.floor(x))  # 向下取整: 3