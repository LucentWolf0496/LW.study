#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    vector<vector<int>> info(n , vector<int> (n , 0));
    for (int i = 0 ; i < n ; i ++){
        info[i][i] = list[i];
    }
    for (int i = 0 ; i < n ; i ++){
        for (int j = i + 1 ; j < n ; j ++){
            info[i][j] = info[i][j - 1] + list[j];
        }
    }
    vector<int> dp(n , 0);
    for (int i = 0 ; i < n ; i ++){
        if (info[0][i] >= 0) dp[i] = 1;
    }
    for (int i = 0 ; i < n ; i ++){
        for (int j = i ; j >= 1 ; j --){
            if (info[j][i] >= 0 && dp[j - 1] != 0) dp[i] = max(dp[i] , dp[j - 1] + 1);
        }
    }
    if (dp[n - 1] == 0) cout << "Impossible";
    else cout << dp[n - 1];
}
