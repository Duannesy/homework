# -*- coding: utf-8 -*-
"""
Created on Sun Feb  4 16:16:09 2024

@author: Duannecy
"""

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
data_url = "http://lib.stat.cmu.edu/datasets/boston"
from sklearn.metrics import mean_squared_error
raw_df = pd.read_csv(data_url, sep=r"\s+", skiprows=22, header=None)
data = np.hstack([raw_df.values[::2, :], raw_df.values[1::2, :2]])
target = raw_df.values[1::2, 2]#导出数据
class GradientDescent:
    def __init__(self, X, y, alpha, epochs):
        self.X = X
        self.y = y
        self.alpha = alpha
        self.epochs = epochs
        self.n = len(y)
        self.theta = np.zeros((X.shape[1]))#数据初始化
 
    def compute_cost(self):
        predictions = self.X @ self.theta
        cost = np.sum((predictions - self.y) ** 2) / (2 * self.n)
        return cost
 
    def gradient_descent(self):
        cost_history = np.zeros(self.epochs)
 
        for epoch in range(self.epochs):
            predictions = self.X @ self.theta
            errors = predictions - self.y
            gradient = (self.X.T @ errors) / self.n
            self.theta = self.theta - self.alpha * gradient
            cost_history[epoch] = self.compute_cost()#梯度下降法
 
        return self.theta, cost_history
    def normal_descent(self):
        return np.linalg.inv(self.X.T @ self.X) @ self.X.T @ self.y#解析法
class StandardScaler:
    def fit(self, X):
        self.mean_ = np.mean(X, axis=0)
        self.std_ = np.std(X, axis=0)
 
    def transform(self, X):
        return (X - self.mean_) / self.std_
 
    def fit_transform(self, X):
        self.fit(X)
        return self.transform(X)
 
 
def train_test_split(data, target, test_size, random_state):
    if random_state is not None:
        np.random.seed(random_state)
 
    n = data.shape[0]
    limit = int(n * test_size)
 
    X_train = data[:-limit]
    X_test = data[-limit:]
    y_train = target[:-limit]
    y_test = target[-limit:]
    return X_train, X_test, y_train, y_test#划分训练集和数据集
 
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(data)
 
alpha = 0.01
epochs = 1000
X_train, X_test, y_train, y_test = train_test_split(X_train_scaled,target, test_size=0.2, random_state=42)
X_test_scaled = scaler.transform(X_test)
 
model = GradientDescent(X_train, y_train, alpha, epochs)#导入类
final_theta, cost_history = model.gradient_descent()#算出
theta_normal = model.normal_descent()
y_pred_normal = X_test @ theta_normal
y_pred_gradient = X_test @ final_theta #计算预测值
mse_normal = mean_squared_error(y_test, y_pred_normal)
mse_gradient = mean_squared_error(y_test,y_pred_gradient)#计算均方误差
print("解析解求解的均方误差：", mse_normal)
print("梯度下降法求解的均方误差：", mse_gradient)
 
# 绘图
plt.plot(range(epochs), cost_history)#画出损失的函数图
plt.xlabel('Iterations')
plt.ylabel('Cost')
plt.title('Gradient Descent Convergence')
plt.figure()   
plt.title("Predication v.s. Ground truth", fontsize=24)
plt.xlabel("ground truth price(unit:$1000)", fontsize=14)
plt.ylabel("predict price", fontsize=14)
plt.scatter(y_test, y_pred_gradient, alpha=0.5)  
plt.plot(y_test, y_test, c='red')
plt.show()

