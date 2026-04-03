import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier, RandomForestRegressor
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error, r2_score

# 1. 加载数据
data = fetch_california_housing()
X, y = data.data, data.target   # y 是连续值，单位：10万美元

# 2. 将连续目标值离散化（分箱）
n_bins = 10
bins = np.percentile(y, np.linspace(0, 100, n_bins + 1))  # 等频分箱
bins[-1] += 1e-5  # 确保最大值落入最后一个区间
y_binned = np.digitize(y, bins[:-1]) - 1   # 得到 0 ~ n_bins-1 的类别标签

# 3. 划分训练集和测试集（一次性划分，同时保留离散标签和连续标签）
X_train, X_test, y_train_binned, y_test_binned, y_train_cont, y_test_cont = train_test_split(
    X, y_binned, y, test_size=0.2, random_state=42
)

# 标准化特征
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 4. 训练分类模型（输出类别概率）
clf = RandomForestClassifier(n_estimators=50, random_state=42)
clf.fit(X_train_scaled, y_train_binned)

# 5. 预测类别概率，并反推出连续值（加权平均）
#    计算每个类别的代表值（这里用每个箱的中位数）
bin_centers = np.array([(bins[i] + bins[i+1]) / 2 for i in range(n_bins)])

# 在测试集上预测概率分布
probs = clf.predict_proba(X_test_scaled)  # shape: (n_samples, n_bins)
y_pred_continuous = np.sum(probs * bin_centers, axis=1)  # 加权平均

# 6. 训练一个直接回归模型作为对比（使用相同的训练集）
reg = RandomForestRegressor(n_estimators=50, random_state=42)
reg.fit(X_train_scaled, y_train_cont)   # 注意：这里用原始的连续 y_train_cont
y_pred_reg = reg.predict(X_test_scaled)

# 7. 评估
mse_cls = mean_squared_error(y_test_cont, y_pred_continuous)
r2_cls = r2_score(y_test_cont, y_pred_continuous)

mse_reg = mean_squared_error(y_test_cont, y_pred_reg)
r2_reg = r2_score(y_test_cont, y_pred_reg)

print("="*50)
print("用分类方式解回归 (分箱+概率加权平均)")
print(f"MSE: {mse_cls:.4f}, R²: {r2_cls:.4f}")
print("\n直接回归模型 (随机森林)")
print(f"MSE: {mse_reg:.4f}, R²: {r2_reg:.4f}")

# 8. 可视化对比
plt.figure(figsize=(8, 4))
plt.scatter(y_test_cont, y_pred_continuous, alpha=0.3, label='分类方式', s=10)
plt.scatter(y_test_cont, y_pred_reg, alpha=0.3, label='直接回归', s=10)
plt.plot([y.min(), y.max()], [y.min(), y.max()], 'k--', lw=1)
plt.xlabel("真实房价 (10万美元)")
plt.ylabel("预测房价")
plt.title("分类解回归 vs 直接回归")
plt.legend()
plt.tight_layout()
plt.show()