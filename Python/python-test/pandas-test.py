# Pandas 在NumPy的基础上构建
# 提供了 DataFrame（类似表格）和 Series（类似带索引的一列）这两种核心数据结构
# 让数据清洗和分析变得非常直观。
import pandas as pd

# 1. 创建DataFrame (可以从字典、列表、文件等创建)
data = {
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [25, 30, 35],
    'City': ['New York', 'London', 'Tokyo']
}
df = pd.DataFrame(data)
print(df)

# 2. 读取/保存文件 (非常方便)
# df = pd.read_csv('data.csv')       # 从CSV文件读取
# df.to_excel('output.xlsx')         # 保存为Excel文件

# 3. 数据查看与筛选
print(df.head(2))                     # 查看前2行
print(df['Name'])                      # 查看Name列
print(df[['Name', 'Age']])             # 查看多列
print(df[df['Age'] > 28])               # 筛选出年龄大于28的行

# 4. 数据清洗
# df.dropna(inplace=True)              # 删除含有缺失值的行
# df.fillna(0, inplace=True)           # 用0填充缺失值
df['Age'] = df['Age'].astype(float)    # 转换数据类型

# 5. 分组与聚合
# 添加一列新数据用于分组示例
df['Department'] = ['HR', 'IT', 'IT']
grouped = df.groupby('Department')['Age'].mean() # 按部门分组，计算平均年龄
print(grouped)