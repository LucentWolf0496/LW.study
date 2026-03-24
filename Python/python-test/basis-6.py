# 使用 try / except / else / finally 处理异常，类似 C++ 的 try-catch。
# 可以捕获特定异常类型，也可以捕获所有异常（不推荐）。
try:
    x = float(input("Enter a number: "))
    result = 10 / x
except ValueError:
    print("That's not a valid number!")
except ZeroDivisionError:
    print("Cannot divide by zero!")
else:
    print(f"Result is {result}")   # 无异常时执行
finally:
    print("Execution finished.")   # 无论是否异常都会执行

import math
print(math.sqrt(16))

from random import randint
print(randint(1, 10))