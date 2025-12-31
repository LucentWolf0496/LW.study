#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int casenum = 0;
    cin >> casenum;
    for (int p = 0 ; p < casenum ; p ++){
        string s;
        cin >> s;
        int n = s.size();
        int result = 0;
        vector<vector<bool>> dp(n + 1 , vector<bool> (n + 1 , false));
        for (int i = 1 ; i <= n ; i ++){
            dp[i][i] = true;
        }
        for (int i = n ; i >= 1 ; i --){
            for (int j = i ; j <= n ; j ++){
                if (i == j){
                    result ++;
                    continue;
                }
                if (i == j - 1){
                    if (s[i - 1] == s[j - 1] || s[i - 1] == '?' || s[j - 1] == '?'){
                        result ++;
                        dp[i][j] = true;
                        continue;
                    }
                    else continue;
                }
                if (s[i - 1] == s[j - 1] || s[i - 1] == '?' || s[j - 1] == '?'){
                    dp[i][j] = dp[i + 1][j - 1];
                }
                else{
                    dp[i][j] = false;
                }
                if (dp[i][j]) result ++;
            }
        }
        cout << result << endl;
    }
}