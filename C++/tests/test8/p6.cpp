#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> score(n + 1);
    for (int i = 1 ; i <= n ; i ++){
        cin >> score[i];
    }
    vector<int> dp(n + 1 , 0);
    for (int i = 1 ; i <= n ; i ++){
        for (int j = 1 ; j <= i ; j ++){
            dp[i] = max(dp[i] , dp[i - j] + score[j]);
        }
    }
    cout << dp[n];
}