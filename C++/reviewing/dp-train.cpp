#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    int n , k;
    cin >> n >> k;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    sort(list.begin() , list.end());
    reverse(list.begin() , list.end());
    list.insert(list.begin() , 0);
    vector<vector<int>> dp(n + 1 , vector<int>(k + 1 , 0));
    for (int i = 1 ; i <= k ; i ++){
        dp[i * 3][i] = dp[i * 3 - 2][i - 1] + (list[i * 3 - 1] - list[i * 3]) * (list[i * 3 - 1] - list[i * 3]);
        for (int j = 3 * i + 1 ; j <= n ; j ++){
            int temp = list[j] - list[j - 1];
            dp[j][i] = min(dp[j - 1][i] , dp[j - 2][i - 1] + temp * temp);
        }
    }
    cout << dp[n][k];
}