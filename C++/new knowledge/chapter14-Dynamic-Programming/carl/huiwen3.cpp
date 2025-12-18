// 统计不同回文序列个数
// 由于“不同”的限制，故需要三维动态规划，分一个维度给最外层的字符
// 注意状态转移方程中+2并不会导致重复！！
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    const int MOD = 1e9 + 7;
    string s;
    int n = s.size();
    vector<vector<vector<int>>> dp(4, vector<vector<int>>(n, vector<int>(n, 0)));
    for (int i = 0; i < n; i++) {
        dp[s[i] - 'a'][i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0, j = len - 1; j < n; i++, j++) {
            for (char c = 'a', k = 0; c <= 'd'; c++, k++) {
                if (s[i] == c && s[j] == c) {
                    dp[k][i][j] = (2LL + dp[0][i + 1][j - 1] + dp[1][i + 1][j - 1]
                         + dp[2][i + 1][j - 1] + dp[3][i + 1][j - 1]) % MOD;// 2LL是强制转化为long long类型！！
                                                                            // +2是更新被剔除的c、cc两个回文子串
                } else if (s[i] == c) {
                    dp[k][i][j] = dp[k][i][j - 1];// 经典的缩略式状态转移方程
                } else if (s[j] == c) {
                    dp[k][i][j] = dp[k][i + 1][j];
                } else {
                    dp[k][i][j] = dp[k][i + 1][j - 1];
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i < 4; i++) {
        res = (res + dp[i][0][n - 1]) % MOD;
    }
    cout << res << endl;
}