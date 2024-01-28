# -*- coding: utf-8 -*-
"""
Created on Sun Jan 28 10:44:26 2024

@author: Duannecy
"""

import warnings
warnings.filterwarnings('ignore')
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt#导入库
train=pd.read_csv(r'C:\Users\Duannecy\Desktop\data\train.csv')#训练集的地址
n=train['Survived'].value_counts()
plt.figure(figsize=(6,6))
plt.pie(n,autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15))
plt.title('total survive')#对总体生存率的统计
sex_count = train.groupby(by='Sex')['Survived'].value_counts()
plt.figure(figsize=(2*5,5))
axes1=plt.subplot(1,2,1)
axes1.pie(sex_count.loc['female'][::-1],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#9400D3','#FFB6C1'],startangle=90)
axes1.set_title('female survive')#对女性生存率统计
axes2=plt.subplot(1,2,2)
axes2.pie(sex_count.loc['male'],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#2E8B57','#AFEEEE'])
axes2.set_title('male survive')#对男性生存率统计
age_range = train['Age']
age_num,_ = np.histogram(age_range,range=[0,80],bins=16)
age_num=[40,22,16,86,114,106,95,72,48,41,32,16,15,4,6,1]
age_survived = []
for age in range(5,81,5):
    survived_num = train.loc[(age_range>=age-5) & (age_range<=age)]['Survived'].sum()
    age_survived.append(survived_num)#统计各年龄段的生存率
age_survived=[31, 11, 11, 37, 45, 48, 51, 39, 23, 21, 15, 8, 6, 0, 0, 1]
plt.figure(figsize=(12,6))
plt.bar(np.arange(2,78,5)+0.5,age_num,width=5,label='total',alpha=0.8)
plt.bar(np.arange(2,78,5)+0.5,age_survived,width=5,label='surivive')#绘制柱状图
plt.legend()
plt.xticks(range(0,81,5))
plt.yticks(range(0,121,10))#设置坐标轴
plt.xlabel('age',position=(0.95,0),fontsize=15)
plt.ylabel('member',position=(0,0.95),fontsize=15)#设置坐标轴信息
plt.title('survive in all age')
plt.grid(True,linestyle=':',alpha=0.6)
embarked_count = train.groupby(by='Embarked')['Survived'].value_counts()
plt.figure(figsize=(3*5,5))
axes1=plt.subplot(1,3,1)
axes1.pie(embarked_count.loc['C'][::-1],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#9400D3','#FFB6C1'],startangle=45)
axes1.set_title('Franch survive')
axes2=plt.subplot(1,3,2)
axes2.pie(embarked_count.loc['Q'],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#4169E1','#AFEEEE'])
axes2.set_title('Ireland survive')
axes3=plt.subplot(1,3,3)
axes3.pie(embarked_count.loc['S'],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#698B69','#76EE00'])
axes3.set_title('England survive')#以上绘制三个饼图，分别代表三个不同港口的生存率
pclass_count = train.groupby(by='Pclass')['Survived'].value_counts()
plt.figure(figsize=(3*5,5))
axes1=plt.subplot(1,3,1)
axes1.pie(pclass_count.loc[1][::-1],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#9400D3','#FFB6C1'],startangle=45)
axes1.set_title('first class survive')
axes2=plt.subplot(1,3,2)
axes2.pie(pclass_count.loc[2],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#4169E1','#AFEEEE'])
axes2.set_title('second class survive')
axes3=plt.subplot(1,3,3)
axes3.pie(pclass_count.loc[3],autopct='%.2f%%',labels=['dead','survive'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1],textprops=dict(size=15),colors=['#698B69','#76EE00'])
axes3.set_title('third class survive')#以上绘制三个饼图，分别代表三个不同舱位的生存率
embarked_pclass = train.groupby(by='Embarked')['Pclass'].value_counts()
plt.figure(figsize=(3*5,5))
axes1=plt.subplot(1,3,1)
axes1.pie(embarked_pclass.loc['C'],autopct='%.2f%%',labels=['first class','third class','second class'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1,0.1],textprops=dict(size=15),colors=['#9400D3','#FFB6C1','#FF6347'])
axes1.set_title('franch survive')
axes2=plt.subplot(1,3,2)
axes2.pie(embarked_pclass.loc['Q'],autopct='%.2f%%',labels=['third class','second class','first class'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1,0.1],textprops=dict(size=10),colors=['#4169E1','#AFEEEE','#66CDAA'],startangle=10)
axes2.set_title('Ireland survive')
axes3=plt.subplot(1,3,3)
axes3.pie(embarked_pclass.loc['S'],autopct='%.2f%%',labels=['third class','second class','first class'],pctdistance=0.4,labeldistance=0.6,shadow=True,explode=[0,0.1,0.1],textprops=dict(size=15),colors=['#698B69','#76EE00','#76EEC6'],startangle=180)
axes3.set_title('England survive')#将舱位和港口的数据关联计算各港口登船的舱位占比
fare_count = train.groupby(by='Fare')['Survived'].value_counts()
fare_count = pd.DataFrame(fare_count)
fare_count.rename(index={'count':'Number'},columns={'count':'Number'},inplace=True)
fare_count.reset_index(inplace=True)#统计不同票价的乘客生还情况
fare_num = fare_count.groupby(by='Fare')['Number'].sum()
fare_num = pd.DataFrame(fare_num)
fare_num.rename(columns={'Number':'Total'},inplace=True)#统计各票价的总人数
fare_survived = fare_count.loc[fare_count['Survived']==1]
fare_survived = fare_survived.merge(fare_num,left_on='Fare',right_index=True,how='inner')
survived_rate = fare_survived['Number'].div(fare_survived['Total'])
survived_rate.index = fare_survived['Fare']#统计各票价的生还人数并计算生还率
fare_death = fare_count.loc[fare_count['Survived']==0]
fare_death = fare_death.merge(fare_num,left_on='Fare',right_index=True,how='inner')
death_rate = fare_death['Number'].div(fare_death['Total'])
death_rate.index = fare_death['Fare']#统计各票价的死亡人数并计算死亡率
plt.figure(figsize=(2*10,5))
axes1=plt.subplot(1,2,1)
axes1.scatter(survived_rate.index,survived_rate,marker='o',color='r')
axes1.set_title('survive and ticket prise')
axes2=plt.subplot(1,2,2)
axes2.scatter(death_rate.index,death_rate,marker='^',color='b')
axes2.set_title('dead and ticket prise')#分别绘制各票价生还率和死亡率的散点图
