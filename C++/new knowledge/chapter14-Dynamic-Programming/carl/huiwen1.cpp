// 最长回文子序列，可删除
// 利用回文串的形式将dp数组对角线初始化
// 注意遍历顺序：从下往上、从左往右递推（由状态转移方程可以推导出来遍历顺序）
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    string s;
    int n = s.size();
    vector<vector<int>> dp(n , vector<int> (n , 0));
    for (int i = 0 ; i < n ; i ++){
        dp[i][i] = 1;
    }
    for (int i = n - 1 ; i >= 0 ; i --){
        for (int j = i ; j < n ; j ++){
            if (s[i] == s[j] && j - i <= 1)
                dp[i][j] = j - i + 1;
            else if (s[i] == s[j] && j - i > 1)
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j] , dp[i][j - 1]);
        }
    }
    cout << dp[0][n - 1] << endl;
}