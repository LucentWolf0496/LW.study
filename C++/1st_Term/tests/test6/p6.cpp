#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n , money , ticket;
    cin >> n >> money >> ticket;
    vector<vector<int>> table(n , vector<int> (n));
    for(int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> table[i][j];
        }
    }
    if (money < ticket){
        cout << "NO" << endl;
        return 0;
    }
    vector<vector<int>> dp(n , vector<int> (n));
    dp[0][0] = table[0][0];
    for (int i = 1 ; i < n ; i ++){
        dp[0][i] = dp[0][i - 1] + table[0][i];
        dp[i][0] = dp[i - 1][0] + table[i][0];
    }
    for (int i = 1 ; i < n ; i ++){
        for (int j = 1 ; j < n ; j ++){
            dp[i][j] = table[i][j] + min(dp[i - 1][j] , dp[i][j - 1]);
        }
    }
    ticket += dp[n - 1][n - 1];
    if (ticket <= money) cout << "YES";
    else cout << "NO";
}