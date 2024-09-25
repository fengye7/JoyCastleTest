/*
要求
1. 实现
GetTopScores 
⽅法，该⽅法接收两个参数：
◦ scores :⼀个整数数组，表⽰所有玩家的分数（分数是不重复的正整数）
◦ m :⼀个整数，表⽰我们想要获取的前⼏名玩家的数量
2. ⽅法应返回⼀个列表，包含前m个最⾼分数，按从⾼到低排序
3. 考虑各种边界情况，例如空数组、m⼤于数组⻓度等
4. 编写单元测试来验证你的实现
5. 分析你的算法的时间复杂度
*/

#include <iostream>
#include <vector>
using namespace std;

/*下面是快速排序*/
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] > pivot) {
            i++; // 类似于记录左边部分有多个数据
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]); // 比较标准放到划分位置
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

vector<int> GetTopScores(vector<int> scores, int m) {
    // 1. 若 scores 为空或 m<=0，返回空列表
    if (scores.empty() || m <= 0) {
        return vector<int>();
    }
    int n = scores.size();
    quickSort(scores, 0, n-1);
    if(m>scores.size()) {
        m = scores.size();
    }
    vector<int> ans;
    ans.assign(scores.begin(), scores.begin()+m);
    return ans;
}

// Test1
void Test1(){
    vector<int> scores{100, 50, 75, 80, 65};
    int m = 3;
    vector<int> ans = GetTopScores(scores, m);
    cout << "Test1 --- Top " << m << " scores: ";
    for(int i=0; i<m; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
void Test2() {
    vector<int> scores{100, 50, 75, 80, 65};
    int m = 10; // m 大于数组长度
    vector<int> ans = GetTopScores(scores, m);
    cout << "Test2 --- Top " << m << " scores: ";
    for (int score : ans) {
        cout << score << " ";
    }
    cout << endl; // 应该输出所有分数
}

void Test3() {
    vector<int> scores{};
    int m = 3; // 空数组
    vector<int> ans = GetTopScores(scores, m);
    cout << "Test3 --- Top " << m << " scores: ";
    for (int score : ans) {
        cout << score << " ";
    }
    cout << endl; // 应该输出空
}

int main() {
    Test1();
    Test2();
    Test3();
    return 0;
}

/*
上面的解法简单使用快排，时间复杂度为O(nlogn)


进阶思考：
对于大规模场景，若m<<scores.size()这时候再排序就得不偿失，做了很多无用功
如何优化？
1. 分布式，利用多核，可将数据分组(n)进行排序，每组取前(m)个，再合并
2. 利用最大堆，每次插入新数据时，会调整堆，这样查询时只需要取前m个即可
3. 局部淘汰，用数组Vec维护前m个最大值，遍历剩下元素（小于Vec中最小值直接丢弃，否则插入并淘汰原最小值），这样时间复杂度为O(n)
*/