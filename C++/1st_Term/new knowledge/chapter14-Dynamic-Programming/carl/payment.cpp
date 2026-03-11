// 0-1背包的又一个变式
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n , t;
    cin >> n >> t;
    vector<int> list(n);
    int sum = 0;
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
        sum += list[i];
    }
    vector<int> dp(sum + 1 , 0);
    for (int i = 0 ; i < n ; i ++){
        for (int j = sum ; j >= list[i] ; j --){
            dp[j] = max(dp[j] , dp[j - list[i]] + list[i]);
        }
    }
    int result = 0;
    for (int i = sum ; i >= t ; i --){
        if (dp[i] == i)
            result = i;
    }
    cout << result << endl;
    return 0;
}