#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// 定义状态结构：数值 + 出现次数
struct State {
    int val;
    int cnt;
};

// 全局变量
// dp[i][j] 存储从第 i 个数到第 j 个数的所有可能结果（去重后）及其频率
// N=16，大小 20x20 足够
vector<State> dp[20][20];
vector<int> nums;
vector<char> ops;

// 辅助数组，用于在合并时快速统计频率
// 值域 -10000 到 10000，偏移量 10000，总大小 20005 足够
// freq_map[v + OFFSET] 存储数值 v 的出现次数
int freq_map[20005]; 
const int OFFSET = 10000;
const int MAX_COUNT = 1005; // 超过1000次就截断，多留一点余量

int main() {
    // 1. 基础 IO 优化
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // 2. 解析输入
    stringstream ss(s);
    int tempNum;
    char tempOp;
    ss >> tempNum;
    nums.push_back(tempNum);
    while (ss >> tempOp >> tempNum) {
        ops.push_back(tempOp);
        nums.push_back(tempNum);
    }

    int n = nums.size();

    // 3. 初始化 DP：叶子节点
    for (int i = 0; i < n; ++i) {
        dp[i][i].push_back({nums[i], 1});
    }

    // 4. 区间 DP 主循环
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            
            // 用于记录当前轮次产生了哪些新数值，以便后续快速清空 freq_map 和构建 dp
            vector<int> distinct_values; 

            // 枚举分割点 k
            for (int k = i; k < j; ++k) {
                char op = ops[k];
                // 引用加速访问
                const vector<State>& leftStates = dp[i][k];
                const vector<State>& rightStates = dp[k+1][j];

                // 核心优化：只枚举去重后的数值进行组合
                for (const auto& l : leftStates) {
                    for (const auto& r : rightStates) {
                        int res = 0;
                        if (op == '+') res = l.val + r.val;
                        else if (op == '-') res = l.val - r.val;
                        else if (op == '*') res = l.val * r.val;
                        
                        // 题目保证绝对值不超过 10000，但做个防御性检查无妨
                        if (res < -10000 || res > 10000) continue; 

                        int idx = res + OFFSET;
                        
                        // 如果是该区间第一次算出这个值，记录下来以便稍后处理
                        if (freq_map[idx] == 0) {
                            distinct_values.push_back(idx);
                        }

                        // 累加次数：次数 = 左边次数 * 右边次数
                        // 优化：次数一旦超过 1000，就可以截断，防止溢出且节省逻辑
                        long long new_count = (long long)freq_map[idx] + (long long)l.cnt * r.cnt;
                        if (new_count > MAX_COUNT) new_count = MAX_COUNT;
                        freq_map[idx] = (int)new_count;
                    }
                }
            }

            // 将统计结果转存回 dp[i][j] 并按值排序（为了后续输出和计算稳定性）
            // 注意：distinct_values 是无序的，需要排序以满足题目输出要求（从小到大）
            sort(distinct_values.begin(), distinct_values.end());
            
            dp[i][j].reserve(distinct_values.size());
            for (int idx : distinct_values) {
                dp[i][j].push_back({idx - OFFSET, freq_map[idx]});
                // 重要：顺手清空 freq_map，避免使用 memset 的开销
                freq_map[idx] = 0; 
            }
        }
    }

    // 5. 输出处理
    // dp[0][n-1] 已经是按 val 排序好的 State 列表
    int printed_count = 0;
    const auto& final_res = dp[0][n-1];
    
    for (const auto& item : final_res) {
        int val = item.val;
        int count = item.cnt;
        
        // 输出该数值 count 次，直到总数达到 1000
        while (count > 0 && printed_count < 1000) {
            cout << val << " ";
            count--;
            printed_count++;
        }
        if (printed_count >= 1000) break;
    }
    // 题目要求最后一个数后面也要有空格，上面循环中已经包含
    // 但如果没有任何输出（极端情况），不需要额外空格。本题保证有解。
    
    return 0;
}