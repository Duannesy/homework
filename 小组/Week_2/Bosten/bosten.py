# -*- coding: utf-8 -*-
"""
Created on Sat Mar 23 13:20:39 2024

@author: Duannecy
"""
import sys
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import math
sns.set()    #设置画图空间为 Seaborn 默认风格
def feature_label_split(pd_data):
    #行数、列数
    row_cnt = pd_data.shape[0]
    column_cnt = len(pd_data.iloc[0,0].split())
    #生成新的X、Y矩阵
    X = np.empty([row_cnt, column_cnt-1])   #生成两个随机未初始化的矩阵
    Y = np.empty([row_cnt, 1])
    for i in range(0, row_cnt):
        row_array = pd_data.iloc[i,0].split()
        X[i] = np.array(row_array[0:-1])
        Y[i] = np.array(row_array[-1])#两个矩阵存储数据并输出
    return X, Y
    

#把特征数据进行标准化为均匀分布
def uniform_norm(X_in):
    X_max = X_in.max(axis=0)
    X_min = X_in.min(axis=0)
    X = (X_in-X_min)/(X_max-X_min)
    return X, X_max, X_min

class linear_regression():

    def fit(self, train_X_in, train_Y, learning_rate=0.03, lamda=0.03, regularization="l2"):
        #样本个数、样本的属性个数
        case_cnt, feature_cnt = train_X_in.shape 
        #X矩阵X0向量
        train_X = np.c_[train_X_in, np.ones(case_cnt, )]
        #初始化待调参数theta
        self.theta = np.zeros([feature_cnt+1, 1])

        max_iter_num = sys.maxsize      #最多迭代次数 
        step = 0                        #当前已经迭代的次数
        pre_step = 0                    #上一次得到较好学习误差的迭代学习次数

        last_error_J = sys.maxsize      #上一次得到较好学习误差的误差函数值
        threshold_value = 1e-6          #定义在得到较好学习误差之后截止学习的阈值
        stay_threshold_times = 10       #定义在得到较好学习误差之后截止学习之前的学习次数

        for step in range(0, max_iter_num):
            #预测值
            pred = train_X.dot(self.theta)
            #损失函数
            J_theta = sum((pred-train_Y)**2) / (2*case_cnt)
            #更新参数theta
            self.theta -= learning_rate*(lamda*self.theta + (train_X.T.dot(pred-train_Y))/case_cnt)          

            #检测损失函数的变化值，提前结束迭代
            if J_theta < last_error_J - threshold_value:
                last_error_J = J_theta
                pre_step = step
            elif step - pre_step > stay_threshold_times:
                break


    def predict(self, X_in):
        case_cnt = X_in.shape[0]
        X = np.c_[X_in, np.ones(case_cnt, )]
        pred = X.dot(self.theta)
        return pred


names=['CRIM','ZN','INDUS','CHAS','NOX','RM','AGE','DIS','RAD','TAX','PTRATIO','B','LSTAT','MEDV']
boston=pd.read_csv("house_data.csv")#导入数据
print(boston.shape)#查看数据集大小
print(boston.info())#查看各字段的基础信息
print(boston.isnull().sum())
corrboston = boston.corr()

plt.figure(figsize=(10,10))    #设置画布
sns.heatmap(corrboston,annot=True,cmap='RdGy')
plt.show()#这是对样本数据变量相关性分析

x_data = boston[['CRIM','ZN','INDUS','CHAS','NOX','RM','AGE','DIS','RAD','TAX','PTRATIO','B','LSTAT']] # 导入所有特征变量
y_data = boston[['MEDV']] # 导入目标值（房价）

plt.figure(figsize=(18,10))

for i in range(13):
    plt.subplot(4,4,i+1)
    plt.scatter(x_data.values[:,i],y_data,s = 5)    #.values将DataFrame对象X_df转成ndarray数组
    plt.xlabel(names[i])
    plt.ylabel('MEDV')
    plt.title(str(i+1)+'. '+names[i]+' - MEDV')  #生成各对字段相关的散点图
    
plt.tight_layout()
plt.show()


data = boston
train_data = pd.read_csv("boston_house.train", header=None)
test_data = pd.read_csv("boston_house.test", header=None)#导入数据集与测试集

#数据预处理，提取标签数据
train_X, train_Y = feature_label_split(train_data)
test_X, test_Y = feature_label_split(test_data)

    #对X（包括train_X, test_X）进行归一化处理，方便后续操作（我搜了好久才知道，self.theta一直异常导致nan）
unif_trainX, X_max, X_min = uniform_norm(train_X)
unif_testX = (test_X-X_min) / (X_max-X_min)

model = linear_regression()
model.fit(unif_trainX, train_Y, learning_rate=0.3, lamda=0.03)
test_pred = model.predict(unif_testX)
test_pred_error = sum((test_pred-test_Y)**2) / (2*unif_testX.shape[0])#计算方差
print("Test error is %d" % (test_pred_error))







