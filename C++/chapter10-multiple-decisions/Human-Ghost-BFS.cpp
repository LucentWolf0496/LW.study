#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct state{
    pair<int, int> left;
    pair<int, int> right;
    int ship;
};

bool operator<(const state& a, const state& b) {
    if (a.left.first != b.left.first) return a.left.first < b.left.first;
    if (a.left.second != b.left.second) return a.left.second < b.left.second;
    if (a.right.first != b.right.first) return a.right.first < b.right.first;
    if (a.right.second != b.right.second) return a.right.second < b.right.second;
    return a.ship < b.ship;
}

bool check1(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的人
    if (l1 < 2) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1 - 2;
    int new_l2 = l2;
    int new_r1 = r1 + 2;
    int new_r2 = r2;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check2(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的人和鬼
    if (l1 < 1 || l2 < 1) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1 - 1;
    int new_l2 = l2 - 1;
    int new_r1 = r1 + 1;
    int new_r2 = r2 + 1;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check3(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的鬼
    if (l2 < 2) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1;
    int new_l2 = l2 - 2;
    int new_r1 = r1;
    int new_r2 = r2 + 2;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check4(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的鬼
    if (l2 < 1) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1;
    int new_l2 = l2 - 1;
    int new_r1 = r1;
    int new_r2 = r2 + 1;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check5(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的人
    if (l1 < 1) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1 - 1;
    int new_l2 = l2;
    int new_r1 = r1 + 1;
    int new_r2 = r2;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check6(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的人
    if (r1 < 2) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1 + 2;
    int new_l2 = l2;
    int new_r1 = r1 - 2;
    int new_r2 = r2;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check7(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的人和鬼
    if (r1 < 1 || r2 < 1) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1 + 1;
    int new_l2 = l2 + 1;
    int new_r1 = r1 - 1;
    int new_r2 = r2 - 1;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check8(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的鬼
    if (r2 < 2) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1;
    int new_l2 = l2 + 2;
    int new_r1 = r1;
    int new_r2 = r2 - 2;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check9(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的鬼
    if (r2 < 1) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1;
    int new_l2 = l2 + 1;
    int new_r1 = r1;
    int new_r2 = r2 - 1;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

bool check10(int l1, int l2, int r1, int r2) {
    // 检查是否有足够的人
    if (r1 < 1) return false;
    
    // 检查运送后的状态是否安全
    int new_l1 = l1 + 1;
    int new_l2 = l2;
    int new_r1 = r1 - 1;
    int new_r2 = r2;
    
    // 左岸安全：如果有人，则人数≥鬼数
    if (new_l1 > 0 && new_l1 < new_l2) return false;
    // 右岸安全：如果有人，则人数≥鬼数
    if (new_r1 > 0 && new_r1 < new_r2) return false;
    
    return true;
}

int main(){
    int thu = 0;
    queue<pair<state, vector<pair<int, int>>>> p;
    set<state> visited;
    state origin = {{3, 3}, {0, 0}, 0};
    vector<pair<int, int>> count(1 , {3 , 3});
    p.push({origin, count});
    visited.insert(origin);

    while(!p.empty()){
        int l1 = p.front().first.left.first;
        int l2 = p.front().first.left.second;
        int r1 = p.front().first.right.first;
        int r2 = p.front().first.right.second;
        int ship = p.front().first.ship;
        vector<pair<int, int>> temp;
        for (int i = 0; i < p.front().second.size(); i++){
            temp.push_back(p.front().second[i]);
        }

        p.pop();
        if (l1 == 0 && l2 == 0){
            for (int i = 0; i < temp.size(); i++){
                cout << i + 1 << ": (" << temp[i].first << "," << temp[i].second << ")" << "\n";
            }
            thu = 1;
            break;
        }

        if (ship == 0){
            if (check1(l1, l2, r1, r2)) {
                state new_state = {{l1 - 2, l2}, {r1 + 2, r2}, 1};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1 - 2, l2});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check2(l1, l2, r1, r2)) {
                state new_state = {{l1 - 1, l2 - 1}, {r1 + 1, r2 + 1}, 1};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1 - 1, l2 - 1});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check3(l1, l2, r1, r2)) {
                state new_state = {{l1, l2 - 2}, {r1, r2 + 2}, 1};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1, l2 - 2});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check4(l1, l2, r1, r2)) {
                state new_state = {{l1, l2 - 1}, {r1, r2 + 1}, 1};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1, l2 - 1});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check5(l1, l2, r1, r2)) {
                state new_state = {{l1 - 1, l2}, {r1 + 1, r2}, 1};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1 - 1, l2});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
        }

        else if (ship == 1){
            if (check6(l1, l2, r1, r2)) {
                state new_state = {{l1 + 2, l2}, {r1 - 2, r2}, 0};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1 + 2, l2});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check7(l1, l2, r1, r2)) {
                state new_state = {{l1 + 1, l2 + 1}, {r1 - 1, r2 - 1}, 0};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1 + 1, l2 + 1});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check8(l1, l2, r1, r2)) {
                state new_state = {{l1, l2 + 2}, {r1, r2 - 2}, 0};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1, l2 + 2});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check9(l1, l2, r1, r2)) {
                state new_state = {{l1, l2 + 1}, {r1, r2 - 1}, 0};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1, l2 + 1});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
            if (check10(l1, l2, r1, r2)) {
                state new_state = {{l1 + 1, l2}, {r1 - 1, r2}, 0};
                if (visited.find(new_state) == visited.end()) {
                    temp.push_back({l1 + 1, l2});
                    p.push({new_state, temp});
                    visited.insert(new_state);
                    temp.pop_back();
                }
            }
        }
    }
    
    // 如果队列为空且没有找到解决方案
    if (thu == 0) {
        cout << "未找到解决方案" << endl;
    }
    
    return 0;
}