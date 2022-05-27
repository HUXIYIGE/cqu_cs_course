# 自定义金矿列表，第一行表示每一个金矿的存储量，第二行表示挖掘该金矿需要的工人数目，
Gold_mine= [[200, 300, 350, 400, 500], [3, 4, 3, 5, 5]]
# 输入工人的数目，方便之后dp列表大小的设定
worker = int(input("请输入工人数量："))
# 标记金矿的数目，方便之后dp列表大小的设定
num = len(Gold_mine[0])
# 动态规划列表
dp = []
# 记录选择了哪些金矿的列表
select = []
'''
假设dp[i][j]为前i座金矿，现有j个工人的时候，可以挖掘的最大黄金储备量，那么递推关系为：
如果现有的工人数目比当前金矿的所需挖掘人数多，那么：dp[i][j]=max{dp[i-1][j],dp[i-1][j-worker[i]]+Gold[i]}
也就是前i座金矿，现有j个工人可以挖掘的最大黄金储备量等于前i-1座，现有j个工人的可挖掘储备量（不挖第i座金矿）和前i-1座，现有j-当前金矿挖掘
人数的储备量+当前金矿的储备量（挖第i座金矿）这两者之间的最大值
如果现有的工人数目小于当前金矿的所需挖掘人数，那么：dp[i][j]=dp[i-1][j]
如果j==0,或者i==0.也就是没有工人和没有金矿，那么相应的dp[i][j]==0
'''
# 初始化dp列表
for i in range(num + 1):
    dp.append([])
    for j in range(worker + 1):
        dp[i].append(0)
# 从第一座金矿到最后一座金矿开始遍历
for i in range(1, num + 1):
    # 每一座金矿从没有工人到全部工人开始遍历
    for j in range(1, worker + 1):
        # 如果当前工人数目大于金矿所需的挖掘人数
        if j - Gold_mine[1][i - 1] >= 0:
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - Gold_mine[1][i - 1]] + Gold_mine[0][i - 1])
        # 现有工人不够挖掘当前金矿
        else:
            dp[i][j] = dp[i - 1][j]
# 输出可以挖掘的最多的黄金储备
print("可以挖掘的最多的黄金储备是：" + str(dp[num][worker]))
# 反向搜索寻找挖掘了那些金矿，原理同0，1背包的选取了哪些物品
while worker > 0 and num > 0:
    # 如果工人数目大于现在的金矿的工人需求
    if worker - Gold_mine[1][num - 1] >= 0:
        # 如果挖现在金矿的收入比不挖高，那么就把现在的金矿标号i加入select列表，否则不作为
        # noinspection PyTypeChecker
        if dp[num - 1][worker - Gold_mine[1][num - 1]] + Gold_mine[0][num - 1] > dp[num - 1][worker]:
            select.append(num)
            worker -= Gold_mine[1][num - 1]
        # 无论挖还是不挖，金矿标号-1
        num -= 1
    # 如果工人数目比现在的金矿的工人需求小，那么肯定不挖，金矿标号-1
    else:
        num -= 1
# 由于是从后往前寻找，顺序是反向的，运用reverse函数倒置列表，变成正序
select.reverse()
# 根据情况输出挖掘了哪些金矿
if len(select) == 0:
    print("应该一座金矿都不挖")
else:
    print("应当挖掘第 ", end='')
    for e in select:
        print(str(e) + " ", end='')
    print("座金矿")
