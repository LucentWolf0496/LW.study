// 完全背包，物品数量没有上限，故需要再嵌套一层循环保证状态转移方程cover掉所有情况之maximum！
// 刚写完就打脸hhh，完全背包支持正序
// 0-1背包只能逆序的本质是只支持选1个，正序会导致选取多个违逆规则
// 但正序恰好就是完全背包所想要的，所以完全背包就正序即可
// 如果将完全背包退化为逆序的0-1背包会多出k这个时间复杂度，不合算

// 打个总结如下：
// 完全背包用正序：允许重复选取（正确做法，simple）
// 完全背包用逆序：每个物品最多选一次（退化为0-1背包）
// 0-1背包只能用逆序：保证每个物品只选一次
// 0-1背包不能用正序：会导致物品被多次选取（错误）
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n , w;
    cin >> n >> w;
    vector<int> list1(n);
    vector<int> list2(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list1[i] >> list2[i];
    }
    vector<int> dp(w + 1 , 0);
    for (int i = 0 ; i < n ; i ++){
        for (int j = list1[i] ; j <= w ; j ++){// 正序遍历，“多次选取”自然被蕴含在正序的遍历之中
            dp[j] = max(dp[j] , dp[j - list1[i]] + list2[i]);
        }
    }
    cout << dp[w] << endl;
    return 0;
}