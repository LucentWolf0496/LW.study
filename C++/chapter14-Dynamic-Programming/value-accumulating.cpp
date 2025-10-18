#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        
        // 读取输入数据
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        
        // dp[i][j] 表示到达第i行第j列的最大价值
        vector<vector<long long>> dp(n, vector<long long>(m, LLONG_MIN));
        
        // 初始化第一行 - 考虑在第一行内移动的情况
        // 从左到右计算第一行的累计最大值
        vector<long long> left(m, LLONG_MIN);
        left[0] = grid[0][0];
        for (int j = 1; j < m; j++) {
            left[j] = max(left[j-1] + grid[0][j], (long long)grid[0][j]);
        }
        
        // 从右到左计算第一行的累计最大值
        vector<long long> right(m, LLONG_MIN);
        right[m-1] = grid[0][m-1];
        for (int j = m-2; j >= 0; j--) {
            right[j] = max(right[j+1] + grid[0][j], (long long)grid[0][j]);
        }
        
        // 合并两个方向的结果
        for (int j = 0; j < m; j++) {
            dp[0][j] = max(left[j], right[j]);
        }
        
        // 动态规划处理其他行
        for (int i = 1; i < n; i++) {
            // 从左到右计算
            vector<long long> left(m, LLONG_MIN);
            for (int j = 0; j < m; j++) {
                // 从上一行同一列下来，或者从左边过来
                if (j == 0) {
                    left[j] = dp[i-1][j] + grid[i][j];
                } else {
                    left[j] = max(dp[i-1][j], left[j-1]) + grid[i][j];
                }
            }
            
            // 从右到左计算
            vector<long long> right(m, LLONG_MIN);
            for (int j = m-1; j >= 0; j--) {
                // 从上一行同一列下来，或者从右边过来
                if (j == m-1) {
                    right[j] = dp[i-1][j] + grid[i][j];
                } else {
                    right[j] = max(dp[i-1][j], right[j+1]) + grid[i][j];
                }
            }
            
            // 合并结果
            for (int j = 0; j < m; j++) {
                dp[i][j] = max(left[j], right[j]);
            }
        }
        
        // 找到最后一行的最大值
        long long result = LLONG_MIN;
        for (int j = 0; j < m; j++) {
            result = max(result, dp[n-1][j]);
        }
        
        cout << result << endl;
    }
    
    return 0;
}