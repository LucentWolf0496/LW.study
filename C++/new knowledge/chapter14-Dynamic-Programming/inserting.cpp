#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main(){
    string s;
    int k;
    cin >> s >> k;
    int t = s.length();
    
    if (t == 1 || k == 0){
        cout << s << endl;
        return 0;
    }
    
    // 预处理：计算从位置i到j组成的数字
    vector<vector<int>> num(t, vector<int>(t, 0));
    for (int i = 0; i < t; i++) {
        for (int j = i; j < t; j++) {
            if (i == j) {
                num[i][j] = s[i] - '0';
            } else {
                num[i][j] = num[i][j-1] * 10 + (s[j] - '0');
            }
        }
    }
    
    // dp[i][j]: 前i+1个数字插入j个乘号的最大乘积
    vector<vector<int>> dp(t, vector<int>(k + 1, 0));
    
    // 初始化：没有乘号的情况
    for (int i = 0; i < t; i++) {
        dp[i][0] = num[0][i];
    }
    
    // 动态规划
    for (int j = 1; j <= k; j++) {  // j: 乘号个数
        for (int i = j; i < t; i++) {  // i: 数字位置（至少需要j+1个数字才能插入j个乘号）
            for (int p = j - 1; p < i; p++) {  // p: 最后一个乘号的位置
                dp[i][j] = max(dp[i][j], dp[p][j - 1] * num[p + 1][i]);
            }
        }
    }
    
    cout << dp[t - 1][k] << endl;
    return 0;
}