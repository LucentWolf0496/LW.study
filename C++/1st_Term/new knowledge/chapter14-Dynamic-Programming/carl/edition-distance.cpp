// 编辑距离
// 初始化：考虑空集，另外一个单词的字符数目就是距离
// 状态转移方程：如果相等则这个字符两边都可以跳过
// 如果不等则需要编辑，有三种就从三者中选最小
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    string s1 , s2;
    cin >> s1 >> s2;
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1 , vector<int> (n + 1 , 0));
    for (int i = 0 ; i <= m ; i ++){
        dp[i][0] = i;
    }
    for (int j = 0 ; j <= n ; j ++){
        dp[0][j] = j;
    }
    for (int i = 1 ; i <= m ; i ++){
        for (int j = 1 ; j <= n ; j ++){// 从1开始遍历！！！
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i - 1][j - 1] , min(dp[i][j - 1] , dp[i - 1][j]));
                // 三种选择选最小：依次对应替换使得位次相等、删除s1一个字符、删除s2一个字符
        }
    }
    cout << dp[m][n] << endl;
    return 0;
}