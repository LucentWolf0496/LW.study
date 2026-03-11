#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <functional>

using namespace std;

// 全局变量
vector<int> sticks;       // 存储木棍长度
vector<bool> used;        // 标记木棍是否被使用
int n;                    // 木棍数量
int target;               // 目标长度（原始木棍长度）
int num;                  // 原始木棍数量

// 深度优先搜索
// 参数：cur_len - 当前正在拼的木棍的已拼长度
//       count - 已经拼好的完整木棍数量
//       start - 开始搜索的木棍索引（剪枝用）
bool dfs(int cur_len, int count, int start) {
    // 如果已经拼好了所有木棍，返回成功
    if (count == num) {
        return true;
    }
    
    // 如果当前木棍已经拼好，开始拼下一根
    if (cur_len == target) {
        return dfs(0, count + 1, 0);
    }
    
    // 记录上次尝试的木棍长度，用于剪枝
    int last_failed = -1;
    
    // 从start开始尝试木棍
    for (int i = start; i < n; i++) {
        // 如果木棍已使用，或者长度大于剩余空间，或者与上次失败的长度相同（剪枝），则跳过
        if (used[i] || cur_len + sticks[i] > target || sticks[i] == last_failed) {
            continue;
        }
        
        used[i] = true;
        if (dfs(cur_len + sticks[i], count, i + 1)) {
            return true;
        }
        used[i] = false;
        
        // 记录失败的长度
        last_failed = sticks[i];
        
        // 剪枝：如果当前木棍是拼一根新木棍的第一段，或者已经拼好了剩余部分，但这次尝试失败，直接返回失败
        if (cur_len == 0 || cur_len + sticks[i] == target) {
            return false;
        }
    }
    
    return false;
}

int main() {
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        
        sticks.resize(n);
        int sum = 0;
        int max_len = 0;
        
        // 读取木棍数据并计算总和和最大长度
        for (int i = 0; i < n; i++) {
            cin >> sticks[i];
            sum += sticks[i];
            max_len = max(max_len, sticks[i]);
        }
        
        // 将木棍从大到小排序，这样DFS时可以更快找到解（剪枝）
        sort(sticks.begin(), sticks.end(), greater<int>());
        
        // 从最大长度开始尝试，因为原始木棍长度不可能小于最大木棍长度
        for (target = max_len; target <= sum; target++) {
            // 如果总长度不能被目标长度整除，则不可能
            if (sum % target != 0) {
                continue;
            }
            
            num = sum / target;  // 原始木棍数量
            used.assign(n, false);  // 重置使用标记
            
            // 尝试用当前目标长度进行拼接
            if (dfs(0, 0, 0)) {
                cout << target << endl;
                break;
            }
        }
    }
    
    return 0;
}