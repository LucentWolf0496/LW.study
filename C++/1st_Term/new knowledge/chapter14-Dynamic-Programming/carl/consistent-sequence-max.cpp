// 最大连续子序列和
// 二维dp和暴力枚举没区别了，故使用一维dp
// 状态转移方程比大小，dp序列定义为以序列数结尾的最大和子序列从而方便连缀加数
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    vector<int> dp(n , 0);
    dp[0] = list[0];
    int result = dp[0];
    for (int i = 1 ; i  < n ; i ++){
        dp[i] = max(dp[i - 1] + list[i] , list[i]);
        result = max(result , dp[i]);
    }
    cout << result << endl;
    return 0;
}