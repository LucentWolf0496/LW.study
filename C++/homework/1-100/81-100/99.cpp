#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> list(n , 0);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    vector<vector<int>> cost(n , vector<int>(n , 0));
    for (int i = 0 ; i < n ; i ++){
        for (int j = i + 1 ; j < n ; j ++){
            for (int k = i ; k <= j ; k ++){
                cost[i][j] += list[k];
            }
        }
    }
    vector<vector<int>> dp(n , vector<int>(n , 100000));
    for (int i = 0 ; i < n ; i ++){
        dp[i][i] = 0;
    }
    for (int i = 1 ; i < n ; i ++){
        for (int j = 0 ; j + i < n ; j ++){
            for (int k = 1 ; k <= i ; k ++){
                int temp = dp[j + k][j + i] + dp[j][j + k - 1] + cost[j][j + i];
                dp[j][j + i] = min(dp[j][j + i] , temp);
            }
            
        }
    }
    cout << dp[0][n - 1] << endl;
}