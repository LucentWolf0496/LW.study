#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> missiles(n);
    for (int i = 0; i < n; i++) {
        cin >> missiles[i];
    }
    
    vector<int> dp(n, 1); // dp[i] 表示以第i个导弹结尾的最长非递增子序列长度
    
    int maxLen = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // 如果第j个导弹高度 >= 第i个导弹高度，可以接在后面
            if (missiles[j] >= missiles[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    
    cout << maxLen << endl;
    return 0;
}