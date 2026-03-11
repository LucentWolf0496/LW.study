// 0-1背包的又一个变式,只不过物品单重和价值都不同
#include <vector>
#include <iostream>
using namespace std;

int main(){
    int t , m;
    cin >> t >> m;
    vector<int> time(m);
    vector<int> price(m);
    for (int i = 0 ; i < m ; i ++){
        cin >> time[i] >> price[i];
    }
    vector<int> dp(t + 1 , 0);
    for (int i = 0 ; i < m ; i ++){
        for (int j = t ; j >= time[i] ; j --){
            dp[j] = max(dp[j] , dp[j - time[i]] + price[i]);// 价值各不同，故需要价值数组存price
        }
    }
    cout << dp[t] << endl;
}