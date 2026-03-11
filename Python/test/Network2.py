import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import numpy as np

# 1. 加载 MNIST 数据集
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

# 2. 数据预处理
# 归一化像素值到 [0,1] 区间，并增加通道维度（因为 CNN 需要 (高, 宽, 通道数)）
x_train = x_train.astype("float32") / 255.0
x_test = x_test.astype("float32") / 255.0
x_train = np.expand_dims(x_train, -1)  # 变成 (60000, 28, 28, 1)
x_test = np.expand_dims(x_test, -1)    # 变成 (10000, 28, 28, 1)

# 将标签转换为 one-hot 编码
y_train = keras.utils.to_categorical(y_train, 10)
y_test = keras.utils.to_categorical(y_test, 10)

# 3. 构建 CNN 模型
model = keras.Sequential([
    # 第一个卷积块
    layers.Conv2D(32, kernel_size=(3, 3), activation='relu', input_shape=(28, 28, 1)),
    layers.MaxPooling2D(pool_size=(2, 2)),

    # 第二个卷积块
    layers.Conv2D(64, kernel_size=(3, 3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2, 2)),

    # 展平特征图，进入全连接层
    layers.Flatten(),

    # 全连接层 + Dropout 防止过拟合
    layers.Dense(128, activation='relu'),
    layers.Dropout(0.5),

    # 输出层（10个类别，softmax激活）
    layers.Dense(10, activation='softmax')
])

# 4. 编译模型
model.compile(
    optimizer='adam',
    loss='categorical_crossentropy',
    metrics=['accuracy']
)

# 打印模型结构
model.summary()

# 5. 训练模型
history = model.fit(
    x_train, y_train,
    batch_size=128,
    epochs=10,
    validation_split=0.2  # 从训练集中划分20%作为验证集
)

# 6. 评估模型
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=0)
print(f"\n测试集准确率: {test_acc:.4f}")