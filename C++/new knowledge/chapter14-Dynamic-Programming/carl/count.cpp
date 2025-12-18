// 给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。
// 初始化：t序列长为0时出现数永远为1，空集合永远出现，其他全部初始化为0即可
// 递推：t序列长度在并非两个字符相等时都不要改变！！
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string s , t;
    cin >> s >> t;
    int p = s.size();
    int q = t.size();
    vector<vector<int>> dp(p + 1 , vector<int>(q + 1 , 0));
    for (int i = 0 ; i <= p ; i ++){
        dp[i][0] = 1;
    }
    for (int i = 1 ; i <= p ; i ++){
        for (int j = 1 ; j <= q ; j ++){
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[p][q] << endl;
    return 0;
}