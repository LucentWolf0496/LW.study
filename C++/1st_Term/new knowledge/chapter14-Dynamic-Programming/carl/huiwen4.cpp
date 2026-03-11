// 找字符串中的五元素回文序列
// 不能暴力动态规划，会导致空间溢出，故需要预处理
// 预处理前后缀个数，然后对每个中间元素遍历即可
// 注意dp引入预处理手段的技巧！！
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string s;
    cin >> s;
    const int MOD = 1e9 + 7;
    int n = s.size();
    if (n < 5) return 0;
        
    // 预处理过程
    // dp1[i][a][b]: 到位置i为止，形如"ab"的子序列数量
    // dp2[i][a][b]: 从位置i开始，形如"ba"的子序列数量
    vector<vector<vector<long long>>> dp1(n, vector<vector<long long>>(10, vector<long long>(10, 0)));
    vector<vector<vector<long long>>> dp2(n, vector<vector<long long>>(10, vector<long long>(10, 0)));
    
    // 计算前缀
    vector<int> cnt(10, 0);
    for (int i = 0; i < n; i++) {
        int d = s[i] - '0';
        if (i > 0) {
            for (int a = 0; a < 10; a++) {
                for (int b = 0; b < 10; b++) {
                    dp1[i][a][b] = dp1[i-1][a][b];
                }
            }
            for (int a = 0; a < 10; a++) {
                dp1[i][a][d] += cnt[a];
            }
        }
        cnt[d]++;
    }
        
    // 计算后缀
    cnt = vector<int>(10, 0);
    for (int i = n-1; i >= 0; i--) {
        int d = s[i] - '0';
        if (i < n-1) {
            for (int a = 0; a < 10; a++) {
                for (int b = 0; b < 10; b++) {
                    dp2[i][a][b] = dp2[i+1][a][b];
                }
            }
            for (int a = 0; a < 10; a++) {
                dp2[i][d][a] += cnt[a];
            }
        }
        cnt[d]++;
    }
        
    long long ans = 0;
    // 枚举中间位置
    for (int i = 2; i < n-2; i++) {
        for (int a = 0; a < 10; a++) {
            for (int b = 0; b < 10; b++) {
                ans = (ans + dp1[i-1][a][b] * dp2[i+1][b][a]) % MOD;
            }
        }
    }

    cout << ans;
}