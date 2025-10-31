#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct state {
    pair<int, int> left;  // (人, 鬼)
    pair<int, int> right; // (人, 鬼)  
    int ship; // 0:左岸, 1:右岸
};

// 重载<运算符用于set
bool operator<(const state& a, const state& b) {
    if (a.left != b.left) return a.left < b.left;
    if (a.right != b.right) return a.right < b.right;
    return a.ship < b.ship;
}

// 检查状态是否合法（任何一边鬼都不能多于人，除非没有人）
bool isValid(state s) {
    // 左岸检查
    if (s.left.first > 0 && s.left.second > s.left.first) return false;
    // 右岸检查
    if (s.right.first > 0 && s.right.second > s.right.first) return false;
    // 人数和鬼数不能为负
    if (s.left.first < 0 || s.left.second < 0 || s.right.first < 0 || s.right.second < 0) return false;
    return true;
}

int main() {
    queue<pair<state, vector<pair<int, int>>>> p;
    set<state> visited; // 记录已访问状态
    
    state origin = {{3, 3}, {0, 0}, 0};
    vector<pair<int, int>> count;
    p.push({origin, count});
    visited.insert(origin);

    while(!p.empty()) {
        state current = p.front().first;
        vector<pair<int, int>> path = p.front().second;
        p.pop();
        
        int l_people = current.left.first;
        int l_ghost = current.left.second;
        int r_people = current.right.first; 
        int r_ghost = current.right.second;
        int ship = current.ship;

        // 检查是否到达目标状态
        if (l_people == 0 && l_ghost == 0) {
            cout << "找到解决方案，共" << path.size() << "步:" << endl;
            for (int i = 0; i < path.size(); i++) {
                cout << "第" << i + 1 << "步: 运送(" << path[i].first << "人," << path[i].second << "鬼)" << endl;
            }
            return 0;
        }

        // 根据船的位置生成新状态
        if (ship == 0) { // 船在左岸
            // 尝试所有可能的运输组合（1-2个生物）
            vector<pair<int, int>> moves = {{1,0}, {2,0}, {0,1}, {0,2}, {1,1}};
            
            for (auto move : moves) {
                int p_move = move.first;
                int g_move = move.second;
                
                // 检查左岸是否有足够的人和鬼
                if (l_people >= p_move && l_ghost >= g_move) {
                    state new_state = {
                        {l_people - p_move, l_ghost - g_move},
                        {r_people + p_move, r_ghost + g_move},
                        1
                    };
                    
                    if (isValid(new_state) && visited.find(new_state) == visited.end()) {
                        vector<pair<int, int>> new_path = path;
                        new_path.push_back({p_move, g_move});
                        p.push({new_state, new_path});
                        visited.insert(new_state);
                    }
                }
            }
        } else { // 船在右岸
            // 尝试所有可能的运输组合（1-2个生物）
            vector<pair<int, int>> moves = {{1,0}, {2,0}, {0,1}, {0,2}, {1,1}};
            
            for (auto move : moves) {
                int p_move = move.first;
                int g_move = move.second;
                
                // 检查右岸是否有足够的人和鬼
                if (r_people >= p_move && r_ghost >= g_move) {
                    state new_state = {
                        {l_people + p_move, l_ghost + g_move},
                        {r_people - p_move, r_ghost - g_move},
                        0
                    };
                    
                    if (isValid(new_state) && visited.find(new_state) == visited.end()) {
                        vector<pair<int, int>> new_path = path;
                        new_path.push_back({p_move, g_move});
                        p.push({new_state, new_path});
                        visited.insert(new_state);
                    }
                }
            }
        }
    }
    
    cout << "未找到解决方案" << endl;
    return 0;
}