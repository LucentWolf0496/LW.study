#include <iostream>
#include <vector>
using namespace std;

int main(){
    int m , n , temp0;
    cin >> m >> n;
    vector<int> temp(m - 1);
    for (int i = 0 ; i < m - 1 ; i ++){
        cin >> temp[i];
    }
    vector<int> dis(m);
    dis[0] = 0;
    for (int i = 1 ; i < m ; i ++){
        dis[i] = dis[i - 1] + temp[i - 1];
    }

    vector<vector<int>> cost(m , vector<int>(m , 0));
    for (int i = 0 ; i < m ; i ++){
        for (int j = i ; j < m ; j ++){
            int mid = (i + j) / 2;
            for (int k = i ; k <= j ; k ++){
                cost[i][j] += abs(dis[k] - dis[mid]);// 三重循环一定要注意最里面的变量要检查！！！半期T2教训！！！
            }                 // 是k而不是i //
        }
    }

    vector<vector<int>> dp(m , vector<int>(n + 1 , 10000000));
    for (int i = 0 ; i < m ; i ++){
        dp[i][1] = cost[0][i];
    }
    for (int i = 2 ; i <= n ; i ++){
        for (int j = i - 1 ; j < m ; j ++){
            for(int k = i - 2 ; k < j ; k ++){
                dp[j][i] = min(dp[j][i] , dp[k][i - 1] + cost[k + 1][j]);
            }
        }
    }
    cout << dp[m - 1][n] << endl;
}