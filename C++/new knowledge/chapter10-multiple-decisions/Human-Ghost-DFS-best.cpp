#include <iostream>
#include <vector>
using namespace std;

// 定义描述渡河状态东岸人数与鬼数的结构变量
struct State {
    int R;    // 状态中的人数
    int G;    // 状态中的鬼数
};

// 函数声明
void display(const vector<State>& states);    // 输出渡河状态
vector<State> transferState();                // 渡河状态转移函数

int main() {
    vector<State> states = transferState();
    display(states);
    return 0;
}

// 渡河状态转移函数
vector<State> transferState() {
    // 摆渡策略
    vector<State> strategies = {{0, 0}, {2, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 2}};
    
    vector<State> states;           // 记录渡河时的状态转移过程
    vector<int> choices;            // 记录状态转移过程的决策号
    
    // 初始状态
    states.push_back({3, 3});       // 初始状态东岸有3人3鬼
    choices.push_back(0);           // 初始选择为0
    
    int k = 0;                      // 当前状态索引
    
    do {
        int direction = 1;          // 摆渡方向，东向西或西向东
        if (k % 2 == 0)             // 偶数表明摆渡要从东岸到西岸
            direction = -1;
        
        int i;                      // 决策号
        // 试探采用哪个决策能安全走1步
        for (i = (k < choices.size() - 1 ? choices[k + 1] + 1 : 1); i <= 5; i++) {
            // 按第i号策略走1步东岸的人数
            int u = states[k].R + direction * strategies[i].R;
            // 按第i号策略走1步东岸的鬼数
            int v = states[k].G + direction * strategies[i].G;
            
            // 检查是否越界
            if (u > 3 || v > 3 || u < 0 || v < 0)
                continue;           // 越界，舍弃当前决策
            
            // 检查是否安全
            bool isSafe = (u == 3 || u == 0 || (u == 1 && v == 1) || (u == 2 && v == 2));
            if (!isSafe) continue;  // 不安全，舍弃当前决策
            
            // 检查是否重复
            bool isDuplicate = false;
            for (int j = k - 1; j >= 0; j -= 2) { // 考虑摆渡方向一致的状态
                if (states[j].R == u && states[j].G == v) { // 人鬼数一致
                    isDuplicate = true;
                    break;
                }
            }
            if (isDuplicate) continue; // 重复，舍弃当前决策
            
            // 找到有效决策，更新状态
            k = k + 1;
            if (k >= states.size()) {
                states.push_back({u, v});
                choices.push_back(i);
            } else {
                states[k] = {u, v};
                choices[k] = i;
            }
            break;
        }
        
        // 所有摆渡决策都尝试了，没成功
        if (i > 5) {
            k = k - 1; // 回溯到前一个状态
        }
        
    } while (!(states[k].R == 0 && states[k].G == 0)); // 目标是东岸既无人又无鬼
    
    // 返回有效状态序列
    return vector<State>(states.begin(), states.begin() + k + 1);
}

void display(const vector<State>& states) {
    for (int i = 0; i < states.size(); i++) {
        cout << i + 1 << ": (" << states[i].R << "," << states[i].G << ")" << endl;
    }
}