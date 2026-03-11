#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    if (n < 3) {
        cout << "N0" << endl;
        return 0;
    }
    
    // 排序数组
    sort(nums.begin(), nums.end());
    
    // dp[i][j] 表示以nums[i]和nums[j]作为最后两个元素的等差数列长度
    vector<vector<int>> dp(n, vector<int>(n, 2));
    // 记录每个值对应的索引（用于快速查找）
    unordered_map<int, int> posMap;
    
    int maxLen = 0;
    int bestStart = -1, bestDiff = -1;
    
    // 初始化dp数组
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int prev = 2 * nums[i] - nums[j];
            
            // 查找是否存在前一个元素
            if (posMap.find(prev) != posMap.end()) {
                int k = posMap[prev];
                dp[i][j] = dp[k][i] + 1;
            }
            
            // 更新最优解
            if (dp[i][j] > maxLen) {
                maxLen = dp[i][j];
                bestStart = nums[j] - (dp[i][j] - 1) * (nums[j] - nums[i]);
                bestDiff = nums[j] - nums[i];
            } else if (dp[i][j] == maxLen && maxLen >= 3) {
                int currentDiff = nums[j] - nums[i];
                int currentStart = nums[j] - (dp[i][j] - 1) * currentDiff;
                
                // 比较公差
                if (currentDiff > bestDiff) {
                    bestStart = currentStart;
                    bestDiff = currentDiff;
                } else if (currentDiff == bestDiff && currentStart > bestStart) {
                    bestStart = currentStart;
                }
            }
        }
        // 记录当前位置，供后续查找使用
        posMap[nums[i]] = i;
    }
    
    // 如果没有找到满足条件的等差数列
    if (maxLen < 3) {
        cout << "N0" << endl;
        return 0;
    }
    
    // 构建结果序列
    vector<int> result;
    for (int i = 0; i < maxLen; i++) {
        result.push_back(bestStart + i * bestDiff);
    }
    
    // 输出结果
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) cout << ",";
        cout << result[i];
    }
    cout << endl;
    
    return 0;
}