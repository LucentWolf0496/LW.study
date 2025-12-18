// 最长公共子序列问题
// dp完成，注意状态转移方程的分类讨论
// 注意多开一格数组可以保证初始化的简洁性
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string s1 , s2;
    cin >> s1 >> s2;
    int p = s1.size();
    int q = s2.size();
    vector<vector<int>> dp(p + 1 , vector<int> (q + 1 , 0));
    for (int i = 1 ; i <= p ; i ++){
        for (int j = 1 ; j <= q ; j ++){
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;// 讨论1：相等就延长
            else
                dp[i][j] = max(dp[i - 1][j] , dp[i][j - 1]); // 讨论2：不相等取最大
        }
    }
    cout << dp[p][q] << endl;// 由于讨论2存在，故直接给出dp[p][q]就是对的
    return 0;
}