#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n , k;
    cin >> n >> k;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++) {
        cin >> list[i];
    }
    sort(list.begin() , list.end());
    reverse(list.begin() , list.end());
    vector<vector<int>> dp(n + 1 , vector<int>(k + 1 , INT_MAX / 2));// 对大值初始化让三倍线的初始化更清爽
    for (int i = 0 ; i <= n ; i ++) {
        dp[i][0] = 0;
    }
    for (int i = 1 ; i <= n ; i ++) {
        for (int j = 1 ; j <= k ; j ++) {
            dp[i][j] = dp[i - 1][j];
            if (i >= 2 && i >= 3 * j) {
                int temp = abs(list[i - 1] - list[i - 2]);
                int q = temp * temp;
                dp[i][j] = min(dp[i][j] , dp[i - 2][j - 1] + q);
            }
        }
    }
    cout << dp[n][k] << endl;
    return 0;
}