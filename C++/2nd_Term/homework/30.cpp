#include <iostream>
#include <set>
#include <map>
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
        // auto it = s.lower_bound({power, 0}); 该句代码的排序逻辑如下
        /*
        set<pair<int, int>> 默认按从小到大排序。
        排序规则：先按first（实力值）升序，实力值相同时按second（id）升序。
        lower_bound({power, 0}) 返回第一个实力值≥power的元素（迭代器指向该元素）。
        迭代器++会移向实力值更大的元素，--会移向实力值更小的元素。
        因此，你的理解完全正确：整个set是有序递增的，后续的prev(it)和it分别代表
        实力值小于power的最大值和大于等于power的最小值。
        */
        int opponent;
        if (it == s.begin()) {
            opponent = it->second;
        } else if (it == s.end()) {
            --it;
            opponent = it->second;
        } else {
            auto prev_it = prev(it);
            int diff_left = power - prev_it->first;
            int diff_right = it->first - power;
            if (diff_left <= diff_right)
                opponent = prev_it->second;
            else
                opponent = it->second;
        }
        cout << id << " " << opponent << endl;
        s.insert({power, id});
    }
    return 0;
}