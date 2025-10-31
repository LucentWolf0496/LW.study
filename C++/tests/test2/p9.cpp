#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;

// 学生状态枚举
enum State {
    SUSCEPTIBLE,  // 易感状态
    INFECTED,     // 生病状态
    IMMUNE        // 免疫状态
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // 构建邻接表
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    
    int initial;
    cin >> initial;
    
    // 如果天数超过这个限制，输出-1
    const long long MAX_DAYS = 2000000000;
    
    // 初始化状态
    vector<State> state(n + 1, SUSCEPTIBLE);
    state[initial] = INFECTED;
    
    // 记录每个学生最近一次被感染的时间
    vector<long long> lastInfectionTime(n + 1, -1);
    lastInfectionTime[initial] = 1;
    
    // 使用优先队列模拟事件，按时间排序
    // 事件类型：感染事件 (时间, 学生ID)
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> events;
    events.push({1, initial});
    
    long long lastInfectionDay = 1;
    
    while (!events.empty()) {
        auto [currentTime, student] = events.top();
        events.pop();
        
        // 如果超过最大天数，结束
        if (currentTime > MAX_DAYS) {
            cout << -1 << endl;
            return 0;
        }
        
        // 如果这个事件已经过时（学生已经被更新到更晚的感染时间），跳过
        if (lastInfectionTime[student] != currentTime) {
            continue;
        }
        
        lastInfectionDay = max(lastInfectionDay, currentTime);
        
        // 更新学生状态为已感染
        state[student] = INFECTED;
        
        // 处理邻居感染
        for (int neighbor : graph[student]) {
            // 计算邻居在当前时间的状态
            State neighborState;
            if (lastInfectionTime[neighbor] == -1) {
                neighborState = SUSCEPTIBLE;
            } else {
                long long infectionTime = lastInfectionTime[neighbor];
                if (currentTime < infectionTime + 1) {
                    neighborState = INFECTED;
                } else if (currentTime < infectionTime + 2) {
                    neighborState = IMMUNE;
                } else {
                    neighborState = SUSCEPTIBLE;
                }
            }
            
            // 如果邻居是易感状态，安排感染事件
            if (neighborState == SUSCEPTIBLE) {
                long long infectionTime = currentTime + 1;
                // 只有当这是邻居的第一次感染或者比上次感染时间更晚时才更新
                if (infectionTime > lastInfectionTime[neighbor]) {
                    lastInfectionTime[neighbor] = infectionTime;
                    events.push({infectionTime, neighbor});
                }
            }
        }
    }
    
    // 流感结束
    cout << lastInfectionDay << endl;
    
    return 0;
}