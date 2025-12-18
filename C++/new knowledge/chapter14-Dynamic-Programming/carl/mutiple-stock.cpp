// 多次股票买卖，不能同时持有股票
// 搞2k+1个状态就好了，奇数序号卖出，偶数序号买入，整体与2stocks类似
// 注意股票不能同时持有————如果可以就退化成了最初的情况，all in最大的购买可能就好了
// 对于冻结期问题，也是通过加【冻结的卖掉状态、持有状态、可购买的卖掉状态】来完成，冻结k天就加k个冻结状态
// 归元合一，重视状态转移
// 有手续费则在方程上-fee即可
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n , k;
    cin >> n >> k;
    vector<int> prices(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> prices[i];
    }
    vector<vector<int>> dp(n , vector<int>(2 * k + 1 , 0));
    for (int i = 0 ; i < k ; i ++){
        dp[0][i * 2 + 1] = - prices[0];
    }
    for (int i = 1 ; i < n ; i ++){
        dp[i][0] = dp[i - 1][0];
        for (int j = 1 ; j <= k ; j ++){
            dp[i][2 * j - 1] = max(dp[i - 1][2 * j - 1] ,
             dp[i - 1][2 * j - 2] - prices[i]);
            dp[i][2 * j] = max(dp[i - 1][2 * j] ,
             dp[i - 1][2 * j - 1] + prices[i]);
        }
    }
    cout << dp[n - 1][2 * k] << endl;
}