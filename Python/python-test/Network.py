import numpy as np

# 1. 定义激活函数（这里使用 Sigmoid）及其导数
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    # 当 x 是 sigmoid 的输出时，导数为 x * (1 - x)
    return x * (1 - x)

# 2. 定义神经网络类
class SimpleNeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size, learning_rate=0.1):
        """
        初始化网络参数
        input_size: 输入层神经元个数
        hidden_size: 隐藏层神经元个数
        output_size: 输出层神经元个数
        learning_rate: 学习率
        """
        # 随机初始化权重和偏置（小随机数有助于打破对称性）
        self.W1 = np.random.randn(input_size, hidden_size) * 0.1   # 输入层->隐藏层权重
        self.b1 = np.zeros((1, hidden_size))                       # 隐藏层偏置
        self.W2 = np.random.randn(hidden_size, output_size) * 0.1  # 隐藏层->输出层权重
        self.b2 = np.zeros((1, output_size))                       # 输出层偏置
        self.lr = learning_rate

    def forward(self, X):
        """
        前向传播
        X: 输入数据，形状 (样本数, 输入维度)
        返回: 输出层的预测值
        """
        # 隐藏层计算
        self.z1 = np.dot(X, self.W1) + self.b1    # 线性组合
        self.a1 = sigmoid(self.z1)                 # 激活（Sigmoid）

        # 输出层计算
        self.z2 = np.dot(self.a1, self.W2) + self.b2
        self.a2 = sigmoid(self.z2)                 # 最终输出

        return self.a2

    def backward(self, X, y, output):
        """
        反向传播（计算梯度）
        X: 输入数据
        y: 真实标签
        output: 前向传播的输出
        """
        m = X.shape[0]  # 样本数量

        # 计算输出层的误差（导数链式法则）
        d_loss_output = (output - y)                # 损失对输出的导数（这里假设使用均方误差）
        d_output = d_loss_output * sigmoid_derivative(output)   # 损失对输出层线性组合 z2 的导数

        # 计算隐藏层的误差
        d_hidden = np.dot(d_output, self.W2.T) * sigmoid_derivative(self.a1)

        # 计算梯度（平均梯度）
        self.dW2 = np.dot(self.a1.T, d_output) / m
        self.db2 = np.sum(d_output, axis=0, keepdims=True) / m
        self.dW1 = np.dot(X.T, d_hidden) / m
        self.db1 = np.sum(d_hidden, axis=0, keepdims=True) / m

    def update_parameters(self):
        """使用梯度下降更新参数"""
        self.W2 -= self.lr * self.dW2
        self.b2 -= self.lr * self.db2
        self.W1 -= self.lr * self.dW1
        self.b1 -= self.lr * self.db1

    def train(self, X, y, epochs):
        """训练网络"""
        for epoch in range(epochs):
            # 前向传播
            output = self.forward(X)

            # 计算损失（均方误差）
            loss = np.mean((output - y) ** 2)

            # 反向传播
            self.backward(X, y, output)

            # 更新参数
            self.update_parameters()

            # 每 1000 轮打印一次损失
            if epoch % 1000 == 0:
                print(f"Epoch {epoch}, Loss: {loss:.6f}")

    def predict(self, X):
        """预测（二分类阈值0.5）"""
        output = self.forward(X)
        return (output > 0.5).astype(int)


# 3. 准备数据：XOR 问题
# 输入有4个样本，每个样本有2个特征
X = np.array([[0, 0],
              [0, 1],
              [1, 0],
              [1, 1]])

# 异或（XOR）的真值表输出
y = np.array([[0],
              [1],
              [1],
              [0]])

# 4. 创建网络并训练
input_size = 2
hidden_size = 4   # 隐藏层神经元数量（可以调整）
output_size = 1
lr = 0.5
epochs = 1000000

nn = SimpleNeuralNetwork(input_size, hidden_size, output_size, lr)
nn.train(X, y, epochs)

# 5. 测试预测
print("\nPredictions after training:")
for i in range(len(X)):
    pred = nn.predict(X[i].reshape(1, -1))  # 预测单个样本
    print(f"{X[i]} -> {pred[0,0]} (true: {y[i,0]})")