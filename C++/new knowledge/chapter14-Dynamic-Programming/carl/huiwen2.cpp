// 回文连续子串数目，依旧是从下往上、从左往右递推
// dp数组索引表示起终子序列是否是回文的，故需要用result变量一个一个++
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    string s;
    int n = s.size();
    vector<vector<int>> dp(n , vector<int>(n , 0));
    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        dp[i][i] = 1;
    }
    for (int i = n - 1 ; i >= 0 ; i --){
        for (int j = i ; j < n ; j ++){
            if (s[i] == s[j] && j - i <= 1)
                dp[i][j] = 1;
            else if (s[i] == s[j] && j - i >= 2)
                dp[i][j] = dp[i + 1][j - 1];
            result += dp[i][j];
        }
    }
    cout << result << endl;
}