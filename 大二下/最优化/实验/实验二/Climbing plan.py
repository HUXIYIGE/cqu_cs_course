# 声明dp列表
dp = []
n = int(input("请输入楼层高度："))
# 初始化动态规划列表,零层楼和一层楼只有一种方案,分别是不动和爬一楼上去
for i in range(n + 1):
    dp.append(0)
dp[0] = 1
dp[1] = 1
# 设dp[i]为爬到第i层的所有方案，爬一次可以爬两楼或者一楼，那么显然：dp[i]=dp[i-1]+dp[i-2] 2,3,.....,n

# 采用自底向上的方法，进行遍历，减少递归算法的重复计算
# 从第二层开始遍历到第n层
for i in range(2, n + 1):
    # 执行递推关系
    dp[i] = dp[i - 1] + dp[i - 2]
# 输出最后的方案
print(str(n) + "层楼一共有" + str(dp[n]) + "种攀爬方案")
