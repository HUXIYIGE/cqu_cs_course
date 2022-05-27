#引入numy库
import numpy as np
#定义雅可比矩阵，x为x1,...,xn的列向量,下方黑塞矩阵亦是
def jacobian(x):
    return np.array([2*x[0]-x[1]-10,2*x[1]-x[0]-4])
#定义黑塞矩阵
def hessian(x):
    return np.array([[2,-1],[-1,2]])
#定义牛顿法，x0为初始的x1,...,xn的列向量
def newton(x0):
    print("初始点为："+str(x0))
    #计数，因为牛顿法存在当初始点远离极小点时，牛顿法产生的点列可能不收敛
    #或者收敛到鞍点，或者Hesse矩阵不可逆，无法计算的问题
    count=1
    #迭代到一千次还没有结果的话，说明无法计算，停止
    count_max=1000
    #x为迭代的解，初始为x0
    x=x0
    #只有当迭代次数小于上限同时雅可比矩阵（梯度向量）不为为零矩阵时才迭代
    while count<=count_max and np.all(jacobian(x)==0)==0:
        #np.linalg.inv()函数为求矩阵的逆函数，np.dot(X,Y)为求矩阵乘积的函数,
        p=np.dot(np.linalg.inv(hessian(x)),jacobian(x))
        x=x-p
        #输出每一次的迭代结果和目标函数值
        print("第"+str(count)+"次迭代结果为： "+"["+str(int(x[0]))+" "+str(int(x[1]))+"]")
        print("第"+str(count)+"次迭代函数值为： "+str(60-10*x[0]-4*x[1]+x[0]*x[0]+x[1]*x[1]-x[0]*x[1])+"\n")
        #计数次数加一
        count+=1
x0=np.array([10,10])
newton(x0)
        
    
    
