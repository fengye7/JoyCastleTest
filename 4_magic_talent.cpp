/*
1. 实现
FindMedianTalentIndex ⽅法，该⽅法接收两个参数：
◦ fireAbility :⼀个已排序（从⼩到⼤）的整数数组，表⽰⽕系魔法能⼒值
◦ iceAbility :⼀个已排序（从⼩到⼤）的整数数组，表⽰冰系魔法能⼒值
2. ⽅法应返回⼀个浮点数，表⽰两组能⼒值合并后的中位数（即综合天赋指数）
3. 编写单元测试来验证你的实现
4. 分析你的算法的时间复杂度和空间复杂度
5. 你的算法应该尽可能⾼效，⽬标是达到尽可能⾼的时间复杂度
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

class TalentAssessmentSystem {
public:
    static double FindMedianTalentIndex(const std::vector<int>& fireAbility, const std::vector<int>& iceAbility) {
        int n = fireAbility.size();
        int m = iceAbility.size();
        
        // 确保 fireAbility 是较小的数组
        if (n > m) {
            return FindMedianTalentIndex(iceAbility, fireAbility);
        }

        int left = 0, right = n;
        int totalHalf = (n + m + 1) / 2;

        while (left <= right) {
            int i = left + (right - left) / 2; // fireAbility 的中间位置
            int j = totalHalf - i; // iceAbility 的对应位置

            // 边界条件
            int fireLeftMax = (i == 0) ? INT_MIN : fireAbility[i - 1];
            int fireRightMin = (i == n) ? INT_MAX : fireAbility[i];
            int iceLeftMax = (j == 0) ? INT_MIN : iceAbility[j - 1];
            int iceRightMin = (j == m) ? INT_MAX : iceAbility[j];

            // 检查是否满足条件
            if (fireLeftMax <= iceRightMin && iceLeftMax <= fireRightMin) {
                // 找到中位数
                if ((n + m) % 2 == 0) {
                    return (std::max(fireLeftMax, iceLeftMax) + std::min(fireRightMin, iceRightMin)) / 2.0;
                } else {
                    return std::max(fireLeftMax, iceLeftMax);
                }
            } else if (fireLeftMax > iceRightMin) {
                right = i - 1; // 减小 fireAbility 的范围
            } else {
                left = i + 1; // 增大 fireAbility 的范围
            }
        }

        throw std::invalid_argument("Input arrays are not sorted.");
    }
};

// 单元测试
void TestFindMedianTalentIndex() {
    assert(TalentAssessmentSystem::FindMedianTalentIndex({1, 3, 7, 9, 11}, {2, 4, 8, 10, 12, 14}) == 8.0);
    assert(TalentAssessmentSystem::FindMedianTalentIndex({2, 7, 9}, {1, 3, 4, 5, 8}) == 4.5);
    assert(TalentAssessmentSystem::FindMedianTalentIndex({1, 2}, {3, 4}) == 2.5);
    assert(TalentAssessmentSystem::FindMedianTalentIndex({1}, {2}) == 1.5);
    assert(TalentAssessmentSystem::FindMedianTalentIndex({}, {1, 2, 3}) == 2.0);
    assert(TalentAssessmentSystem::FindMedianTalentIndex({1, 2, 3}, {}) == 2.0);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    TestFindMedianTalentIndex();
    return 0;
}

//时间复杂度：O(log(min(n, m)))，其中 n 和 m 是两个数组的长度，因为我们在较小数组上进行二分查找。
//空间复杂度：O(1)

/*
进阶挑战?
1. 如果我们需要实时更新⼤量学徒的天赋指数，你会如何优化你的算法或数据结构？
答：1》动态的数据结构，如红黑树维护天赋指数，这样可以快速的插入或删除或查找
    2》分开处理较大值和较小值，小根堆处理较大部分，大根堆处理较小部分，保持两个堆的大小差不多，维护两个堆的平衡

2. 在游戏的⾼级模式中，可能会有更多的魔法属性（不仅仅是⽕和冰）。你的算法如何扩展到处理k个有序数组的中位数？
答：1》分组处理，发挥多核优势
    2》使用归并排序或分治来处理k个有序数组的中位数，在每一组中找到中位数，然后在这k个中位数中找到中位数
*/


/*
创意思考?
这个天赋评估系统如何影响游戏的⻆⾊发展和技能学习机制？你能想到如何将这个概念融⼊到游戏的其他⽅⾯，⽐如任务系统或PVP对战中吗？
答：1》角色发展：天赋指数可以决定他们在特定魔法领域中的成长速度（较高的火系天赋可能使学徒在学习火系技能时获得经验加成）
    2》技能学习机制：可以设计一个技能树，基于天赋指数解锁不同的技能（天赋指数达到一定水平后，可以解锁更高级的技能或魔法）
    3》任务系统：根据学徒的天赋指数设计任务（某些任务可能要求学徒具备特定的天赋指数才能完成？或者完成任务后根据表现提高天赋指数？）
    4》PVP 对战：PVP中，天赋指数可以作为匹配机制因子
    5》社交互动：根据天赋指数合作（一定天赋值范围内才可以组队？不同的天赋指数偏向平衡队伍属性？）
*/