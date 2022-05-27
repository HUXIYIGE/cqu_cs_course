# coding=utf-8
def Max_Profit():
    # 输入股票价格的列表，并对其做去"[","]",","符号的操作
    string = input("请输入股票价格的列表：")
    string = string.replace("[", "")
    string = string.replace("]", "")
    string = string.replace(",", "")
    # 去掉空字符
    string = string.split()
    # 将字符串加入列表，形成列表如：[1,2,3,4]
    price=[]
    for e in string[0]:
        price.append(e)
    # 记录列表长度方便计算
    size = len(price)
    '''
    假设dp[i][0]表示第i天手里没有股票的最大收益
    dp[i][1]表示第i天手里有股票的最大收益
    首先，如果第i天手里没有股票，那么有两种可能：
    （1）前一天手里还有股票，今天卖了
    （2）昨天手里就没有股票
    那么可以得到递推关系：
    dp[i,0]=max{dp[i-1,0],dp[i-1,1]+price[i]}
    其次，如果第i天手里有股票，那么有两种可能：
    （1）今天刚刚买的股票
    （2）昨天就已经有股票在手上了
    那么可以得到递推关系：
    dp[i,1]=max{dp[i-1,1],dp[i-1,0]-price[i]}
    很明显dp[0,0]的值为零，dp[0,1]的值为-price[0]
    '''
    # 通过观察可以发现，求第i天的最大收入
    # 递归只使用了dp[i-1,0]和dp[i-1,1]
    # 所以我们只需要存储一个值即可，并在循环中不断地去更新
    dp0 = 0
    dp1 = -int(price[0])
    for i in range(0, size):
        tempdp0 = max(dp0, dp1 + int(price[i]))
        tempdp1 = max(dp1, dp0 - int(price[i]))
        dp0 = tempdp0
        dp1 = tempdp1
    print("最大获利：" + str(dp0))


Max_Profit()
