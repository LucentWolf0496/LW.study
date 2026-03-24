# NumPy 是Python数据科学栈的基石，其核心是 ndarray（N维数组）对象，运算速度远快于Python的原生列表。
import numpy as np

# 1. 创建数组
arr1 = np.array([1, 2, 3, 4, 5])          # 从列表创建一维数组
arr2 = np.array([[1, 2], [3, 4]])         # 创建二维数组（矩阵）
zeros = np.zeros((3, 4))                   # 创建3行4列的全0数组
ones = np.ones((2, 3))                     # 创建2行3列的全1数组
range_arr = np.arange(0, 10, 2)             # 类似range()，创建 [0, 2, 4, 6, 8]
random_arr = np.random.rand(3, 3)           # 创建3x3的随机数组（值在0到1之间）

# 2. 数组运算 (向量化操作，无需显式循环)
a = np.array([1, 2, 3])
b = np.array([4, 5, 6])
print(a + b)          # 对应元素相加: [5 7 9]
print(a * 2)          # 标量乘法: [2 4 6]
print(a ** 2)         # 每个元素平方: [1 4 9]
print(np.sqrt(a))     # 每个元素开方: [1. 1.414 1.732]

# 3. 索引和切片 (类似Python列表，但更强大)
matrix = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print(matrix[0, 1])    # 第1行第2列的元素: 2
print(matrix[1:, :2])  # 第2行及以后，前两列: [[4 5], [7 8]]

# 4. 统计运算
data = np.array([1, 2, 3, 4, 5])
print(data.mean())     # 平均值: 3.0
print(data.sum())      # 总和: 15
print(data.max())      # 最大值: 5

#你的报错是因为文件命名冲突：你将当前Python脚本命名为 numpy.py
# 然后又在代码中写 import numpy as np。Python 导入模块时，会先在当前脚本所在目录查找
# 结果找到了你写的 numpy.py 文件（而不是系统安装的真正的 numpy 库），导致导入失败，所以提示 'array' 属性不存在。
# 解决方法很简单：
# 把你写的这个文件重命名，不要使用 numpy.py 这种与第三方库相同的名字
# 比如改为 test_numpy.py 或任何其他不冲突的名字，然后重新运行即可。
# !!!不要使用有歧义的文件名称!!!