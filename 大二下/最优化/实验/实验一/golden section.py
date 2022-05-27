import math
print("目标函数为："+"f(x)=8*exp(1-x)+7*log(x)"+"\n")
#记录迭代次数
count=0
#初始的区间[a,b]和区间精度c
a=int(input("请输入起始区间的第一个数字（整数）："))
b=int(input("请输入起始区间的第二个数字（整数）："))
c=float(input("请输入区间精度(浮点数)："))
#初始的迭代点a1和a2，初始的函数值f1和f2
a1=b-0.618*(b-a)
a2=a+0.618*(b-a)
f1=8*math.exp(1-a1)+7*math.log(a1)
f2=8*math.exp(1-a2)+7*math.log(a2)
#当区间长度b-a小于c一直迭代
while(b-a>c):
    #如果左边的函数值大于右边的，那么收缩左边区间
    if f1>f2:
        a=a1
        a1=a2
        f1=f2
        a2=a+0.618*(b-a)
        f2=8*math.exp(1-a2)+7*math.log(a2)
    #如果右边的函数值大于左边的，那么收缩右边区间
    else:
        b=a2
        a2=a1
        f2=f1
        a1=b-0.618*(b-a)
        f1=8*math.exp(1-a1)+7*math.log(a1)
    #迭代次数加一
    count+=1
    print("第"+str(count)+"次迭代的区间结果是："+"["+str('%.3f'% a)+","+str('%.3f'% b)+"]")
    temp=8*math.exp(1-((a+b)/2))+7*math.log(((a+b)/2))
    print("第"+str(count)+"次迭代的函数值是："+str('%.3f'%temp))
    print("\n")

    
