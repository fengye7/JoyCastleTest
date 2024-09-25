/*
要求
1. 实现MaxTreasureValue 
⽅法，该⽅法接收⼀个参数：
◦ treasures :⼀个整数数组，表⽰每个宝箱中宝物的价值
2. ⽅法应返回⼀个整数，表⽰在不触发陷阱的情况下，玩家能够获得的最⼤宝物总价值
3. 编写单元测试来验证你的实现
4. 分析你的算法的时间复杂度和空间复杂度
*/

#include <iostream>
#include <vector>
#include <cassert>

class TreasureHuntSystem {
public:
    static int MaxTreasureValue(const std::vector<int>& treasures) {
        // 边界情况：如果数组为空，返回0
        if (treasures.empty()) return 0;

        int n = treasures.size();
        if (n == 1) return treasures[0];

        // 动态规划数组
        std::vector<int> dp(n, 0);
        
        // 初始化前两个宝箱的最大值
        dp[0] = treasures[0];
        dp[1] = std::max(treasures[0], treasures[1]);

        // 填充动态规划数组
        for (int i = 2; i < n; i++) {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + treasures[i]);
        }

        return dp[n - 1] < 0 ? 0:dp[n-1]; // 返回最后一个状态的最大值
    }
};

// 单元测试
void TestMaxTreasureValue() {
    assert(TreasureHuntSystem::MaxTreasureValue({3, 1, 5, 2, 4}) == 12); // 3 + 5 + 4
    assert(TreasureHuntSystem::MaxTreasureValue({2, 7, 9, 3, 1}) == 12); // 2 + 9 + 1
    assert(TreasureHuntSystem::MaxTreasureValue({1, 2, 3, 1}) == 4); // 1 + 3
    assert(TreasureHuntSystem::MaxTreasureValue({5, 5, 10, 100, 10, 5}) == 110); // 5 + 100 + 5
    assert(TreasureHuntSystem::MaxTreasureValue({}) == 0); // 空数组
    assert(TreasureHuntSystem::MaxTreasureValue({-1, -2, -3, -4}) == 0); // 负值情况

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    TestMaxTreasureValue();
    return 0;
}

//时间复杂度：O(n)
//空间复杂度：O(n)（可优化掉存储数组只维护两个变量）

/*
进阶思考：
1. 如果我们允许玩家使⽤⼀次"魔法钥匙"，可以安全地打开任意两个相邻的宝箱⽽不触发陷阱，你会如何修改你的算法？
答：在动态规划中加入一个额外的状态，表示是否使用了魔法钥匙。这样可以在处理相邻宝箱时考虑使用钥匙的情况。

2. 在游戏的⾼级关卡中，有些宝箱可能包含负值（表⽰陷阱会扣除玩家的分数）。你的算法如何处理这种情况？
答：在选择宝箱时需要考虑不选择某些宝箱，以避免损失。在动态规划中，可以在状态转移时判断当前选择是否会导致总体价值下降。
*/

/*
创意思考？
这个机制可能会在游戏中带来哪些有趣的策略选择？你能想到如何将这个概念扩展到⼀个完整的游戏关卡设计中吗？
答：1》不同组合，不同策略，不同结果。
    2》不同种类宝箱
    3》开箱限制（钥匙种类）
    4》陷阱增多（陷阱宝箱：所得全丢或丢一部分）
    5》增加时间机制（这时需要考虑宝箱数量；不同种宝箱的开箱时间：开箱或移动速度的buff的增益减益）
    6》宝箱可被人争抢（多人在线游戏）
*/