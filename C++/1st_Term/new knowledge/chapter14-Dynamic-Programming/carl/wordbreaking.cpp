//单词切块字典搜索问题
//本质上其实是对排序有要求的完全背包问题，所以要外容量内字典构建循环
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> wordDict(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> wordDict[i];
    }
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for (int i = 1 ; i <= s.size() ; i ++) {
        for (int j = 0 ; j < i ; j ++) {
            string word = s.substr(j, i - j);
            for (int k = 0 ; k < n ; k ++){
                if (wordDict[k] == word && dp[j])
                    dp[i] = true;
            }
        }
    }
    cout << (dp[s.size()] ? "true" : "false") << endl;
}