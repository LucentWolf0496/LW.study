// 跳步游戏，数组标定每个格子可以跳的最远距离，非负，问能否到终点
// 动态规划需要O(n^2)，而贪心只需要O(n)
// 贪心就是逐步更新最远覆盖范围的思想！！！类似模拟题第7题的奶牛听音乐！！！
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> nums;
    int n = nums.size();
    int max1 = 0;
    for (int i = 0 ; i < n && i <= max1 ; i ++){
        max1 = max(max1 , nums[i] + i);// 要正确更新状态
    }
    if (max1 >= n - 1) cout << 1 << endl;
    else cout << 0 << endl;
}