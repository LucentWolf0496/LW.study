// 允许两次股票的买入卖出，但是同时最多只可持有一股股票
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
    vector<vector<int>> dp(n , vector<int> (5 , 0));
    dp[0][1] = - list[0];
    dp[0][3] = - list[0];
    for (int i = 1 ; i < n ; i ++){
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = max(dp[i - 1][1] , dp[i - 1][0] - list[i]);
        dp[i][2] = max(dp[i - 1][2] , dp[i - 1][1] + list[i]);
        dp[i][3] = max(dp[i - 1][3] , dp[i - 1][2] - list[i]);
        dp[i][4] = max(dp[i - 1][4] , dp[i - 1][3] + list[i]);
    }
    cout << dp[n - 1][4] << endl;
}