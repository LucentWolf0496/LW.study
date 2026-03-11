#include <iostream>
#include <vector>
#include <algorithm>
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
    vector<vector<int>> dp(k + 1 , vector<int>(n + 1 , 0));
    for (int i = 1 ; i <= k ; i ++){
        int temp = list[i * 3 - 1] - list[i * 3 - 2];
        dp[i][i * 3] = dp[i - 1][i * 3 - 2] + temp * temp;
        for (int j = 3 * i + 1 ; j <= n ; j ++){
            int temp2 = list[j - 1] - list[j - 2];
            dp[i][j] = min (dp[i][j - 1] , dp[i - 1][j - 2] + temp2 * temp2);
        }
    }
    cout << dp[k][n] << endl;
}