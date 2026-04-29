#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n >> x >> y;

    // 哈希表：学生名 -> {总分，课程数}
    unordered_map<string, pair<int, int>> stats;

    for (int i = 0; i < n; ++i) {
        string course, student;
        int score;
        cin >> course >> student >> score;
        stats[student].first += score;
        stats[student].second += 1;
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        string student;
        cin >> student;
        auto it = stats.find(student);
        int total = it->second.first;
        int cnt = it->second.second;
        // 条件：课程数 >= x 并且 平均分 > y
        if (cnt >= x && total > y * cnt) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }

    return 0;
}