# PyTorch 是目前人工智能研究领域最核心的框架之一
# 它以灵活、直观、Pythonic 的特点，成为了学术界和工业界开发者的首选
# 你可以把它想象成一个包含了张量、自动微分和神经网络模块的工具箱。
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset

# 1. 数据准备 (Data Preparation)
# 你需要自定义一个 Dataset 类来读取你的数据
class MyDataset(Dataset):
    def __init__(self):
        # 初始化数据路径或生成数据
        self.data = torch.randn(100, 10) # 假设有100个样本，每个10维
        self.labels = torch.randint(0, 2, (100,))

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return self.data[idx], self.labels[idx]

dataset = MyDataset()
dataloader = DataLoader(dataset, batch_size=32, shuffle=True)

# 2. 模型定义 (Model Definition)
class MyModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(10, 20)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(20, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        x = self.sigmoid(x)
        return x

model = MyModel()

# 3. 损失函数和优化器选择 (Loss & Optimizer)
criterion = nn.BCELoss()  # 二分类交叉熵损失
optimizer = optim.Adam(model.parameters(), lr=0.001)

# 4. 训练循环 (Training Loop)
num_epochs = 5
for epoch in range(num_epochs):
    for inputs, labels in dataloader:
        # 前向传播
        outputs = model(inputs)
        loss = criterion(outputs.squeeze(), labels.float())

        # 反向传播和优化
        optimizer.zero_grad() # 梯度清零
        loss.backward()        # 自动计算梯度
        optimizer.step()       # 更新参数

    print(f'Epoch [{epoch+1}/{num_epochs}], Loss: {loss.item():.4f}')

print("训练完成！")