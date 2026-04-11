// 用set加上lower_bound的迭代器处理复杂问题
// 注意lower_bound的使用和prev对于迭代器的加工
#include <iostream>
#include <set>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<pair<int, int>> s;
    s.insert({1000000000, 1});
    for (int i = 0; i < n; ++i) {
        int id, power;
        cin >> id >> power;
        auto it = s.lower_bound({power, 0});
        int opponent = -1;
        int best_diff = INT_MAX;
        if (it != s.end()) {
            int diff = it->first - power;
            auto first_it = s.lower_bound({it->first, -1});
            if (diff < best_diff) {
                best_diff = diff;
                opponent = first_it->second;
            } else if (diff == best_diff) {
                if (first_it->second < opponent) opponent = first_it->second;
            }
        }
        if (it != s.begin()) {
            auto prev_it = prev(it);
            auto first_prev = s.lower_bound({prev_it->first, -1});
            int diff = power - prev_it->first;
            if (diff < best_diff) {
                best_diff = diff;
                opponent = first_prev->second;
            } else if (diff == best_diff) {
                if (first_prev->second < opponent) opponent = first_prev->second;
            }
        }
        cout << id << " " << opponent << endl;
        s.insert({power, id});
    }
    return 0;
}