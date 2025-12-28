#include <iostream>
#include <vector>
using namespace std;

vector<int> list;
vector<bool> check;
vector<bool> init;

int main(){
    int n , m ;
    cin >> n >> m;
    list.resize(n);
    check.resize(m + 1);
    init.resize(m + 1);
    for (int i = 1 ; i <= m ; i ++){
        check[i] = false;
        init[i] = false;
    }
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    vector<int> dp(n);
    for (int i = 0 ; i < n ; i ++){
        dp[i] = i + 1;
    }
    for (int i = 0 ; i < list.size() ; i ++){
        if (dp[i] == dp[i + 1]){
            list.erase(list.begin() + i);
            i --;
        }
    }
    n = list.size();
    for (int i = 0 ; i < n ; i ++){
        int count = 0;
        for (int j = i ; j >= 0 ; j --){
            if (j == i) 1;
            else if (j + 1 == i) dp[i] = min(dp[i] , dp[j] + 1);
            else dp[i] = min(dp[i] , dp[j] + count * count);
            if (!check[list[j]]){
                count ++;
                check[list[j]] = true;
            }
            if (count * count >= dp[i]) break;
        }
        check = init;
    }
    cout << dp[n - 1];
}