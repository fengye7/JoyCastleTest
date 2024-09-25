/*
1. 实现
MaxEnergyField⽅法，该⽅法接收⼀个参数：
◦ heights :⼀个整数数组，表⽰在每个位置能建造的能量塔的最⼤⾼度
2. ⽅法应返回⼀个浮点数，表⽰能创造的最⼤魔法能量场强度（即两座塔与x轴构成的最⼤梯形⾯
积）
3. 编写单元测试来验证你的实现
4. 分析你的算法的时间复杂度和空间复杂度
*/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class EnergyFieldSystem
{
public:
    static float MaxEnergyField(vector<int> &heights)
    {
        int n = heights.size();
        int l = 0, r = n - 1;
        float maxArea = 0.0f;
        while (l < r)
        {
            maxArea = max(maxArea, (float)(heights[l] + heights[r]) * (r - l) / 2);

            // 移动较矮的高度
            if (heights[l] < heights[r])
            {
                l++;
            }
            else
            {
                r--;
            }
        }
        return maxArea;
    }
};
// 单元测试
void TestMaxEnergyField()
{
    std::vector<int> heights1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    assert(EnergyFieldSystem::MaxEnergyField(heights1) == 52.5f);

    std::vector<int> heights2 = {1, 1};
    assert(EnergyFieldSystem::MaxEnergyField(heights2) == 1.0f); // 1 * 1 / 2

    std::vector<int> heights3 = {4, 3, 2, 1, 4};
    assert(EnergyFieldSystem::MaxEnergyField(heights3) == 16.0f); // 4 * 4 / 2

    std::vector<int> heights4 = {};
    assert(EnergyFieldSystem::MaxEnergyField(heights4) == 0.0f); // 空数组情况

    std::vector<int> heights5 = {5};
    assert(EnergyFieldSystem::MaxEnergyField(heights5) == 0.0f); // 只有一个塔

    std::cout << "All tests passed!" << std::endl;
}

int main()
{
    TestMaxEnergyField();
    return 0;
}

// 时间复杂度：O(n)
// 空间复杂度：O(1)

/*
1. 如果我们允许玩家使⽤魔法道具来临时增加某个位置的塔的⾼度，你会如何修改你的算法？
答：考虑可使用魔法道具数量n; 考虑每个道具可增加的高度h
    1》那么总增高度为 n*m = K
    2》考虑增加的高度在左右两边的分配不影响结果即（上底加下底）
    3》考虑引入道具后单次最大能量场增量为 K*(r-l)/2将这个加入上面的判断条件
    4》若考虑多次建能量场，则需要动态规划本次使用多少对后续最大值的影响

2. 在游戏的⾼级模式中，某些位置可能有建筑限制（⾼度为0）。你的算法如何处理这种情况？
答：预处理heights数组，将高于限高的位置重新设置为限高，再进行后续计算

*/

/*
创意思考
这个能量场机制如何影响玩家在游戏中的策略选择？你能想到如何将这个概念扩展到⼀个有趣的游戏
玩法中吗？

答：1》首先要考虑这个能量场机制设定的作用（仅防御消除该范围的投掷攻击？格挡所有能量场覆盖高度内的攻击？能量场能主动攻击？攻击的机制与频率？）
    2》然后考虑这个能量场机制如何影响玩家的策略选择（如何选择能量场的位置？如何选择能量场的高度？如何选择能量场的数量？）
    3》玩家的策略选择与游戏方式有关（是用能量场收集目标物？还是阻隔敌人？还是增强自身属性？）
    4》若是阻击敌人，能量场的建造策略就和敌人生成算法相关
    5》如何扩展？
        * 能量场种类（防，攻，召唤，减益，增幅）
        * 位置选择增加（可空中、水中制造）==》进一步，空中、水中作用种类变异
        * 形状增加（提升自由度）
        * 限制增加（限高、限大小、限数量）
        * 使用能量场的消耗物
*/