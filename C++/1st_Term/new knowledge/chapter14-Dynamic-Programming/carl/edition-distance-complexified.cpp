// 编程网格式的编辑距离程序，包含字典与待检查的单词
// 依旧是动态规划~注意初始化与状态转移的思维细节
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    vector<string> dict;
    vector<string> list;
    string s;
    while(cin >> s && s != "#"){
        dict.push_back(s);
    }
    while(cin >> s && s != "#"){
        list.push_back(s);
    }
    for (int i = 0 ; i < list.size() ; i ++){
        cout << list[i];
        vector<string> temp;
        bool check = false;
        for (int j = 0 ; j < dict.size() ; j ++){
            string s1 = list[i];
            string s2 = dict[j];
            int m = s1.size();
            int n = s2.size();
            vector<vector<int>> dp(m + 1 , vector<int> (n + 1 , 0));
            for (int p = 0 ; p <= m ; p ++){
                dp[p][0] = p;
            }
            for (int q = 0 ; q <= n ; q ++){
                dp[0][q] = q;
            }
            for (int p = 1 ; p <= m ; p ++){
                for (int q = 1 ; q <= n ; q ++){
                    if (s1[p - 1] == s2[q - 1])
                        dp[p][q] = dp[p - 1][q - 1];
                    else
                        dp[p][q] = 1 + min(dp[p - 1][q - 1] , min(dp[p - 1][q] , dp[p][q - 1]));
                }
            }
            int result = dp[m][n];
            if (result == 0){
                check = true;
                break;
            }
            if (result == 1)
                temp.push_back(s2);
            }
        if (check)
            cout << " is correct" << endl;
        if (!check){
            cout << ":";
            for (int j = 0 ; j < temp.size() ; j ++){
                cout << " " << temp[j];
            }
            cout << endl;
        }
    }
}