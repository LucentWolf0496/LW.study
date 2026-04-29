#include <iostream>
#include <map>      // 使用 multimap 需要包含此头文件
#include <string>
using namespace std;

class CStudent {
public:
    struct CInfo {          // 类内部可以定义类
        int id;
        string name;
    };
    int score;
    CInfo info;             // 学生的其他信息
};

typedef multimap<int, CStudent::CInfo> MAP_STD;

int main() {
    MAP_STD mp;
    CStudent st;
    string cmd;

    while (cin >> cmd) {
        if (cmd == "Add") {
            cin >> st.info.name >> st.info.id >> st.score;
            mp.insert(MAP_STD::value_type(st.score, st.info));
        }
        else if (cmd == "Query") {
            int score;
            cin >> score;
            MAP_STD::iterator p = mp.lower_bound(score);   // 第一个成绩 >= score

            if (p != mp.begin()) {   // 存在成绩比 score 低的学生
                --p;                 // 指向成绩小于 score 的最大元素
                int targetScore = p->first;        // 比查询分数低的最高分
                MAP_STD::iterator maxp = p;
                int maxId = p->second.id;

                // 向前遍历所有成绩等于 targetScore 的学生，找出最大 id
                for (; p != mp.begin() && p->first == targetScore; --p) {
                    if (p->second.id > maxId) {
                        maxp = p;
                        maxId = p->second.id;
                    }
                }
                // 处理 p == mp.begin() 且该元素成绩也等于 targetScore 的情况
                if (p->first == targetScore) {
                    if (p->second.id > maxId) {
                        maxp = p;
                        maxId = p->second.id;
                    }
                }
                cout << maxp->second.name << " " << maxp->second.id << " " << maxp->first << endl;
            }
            else {
                // lower_bound 返回 begin()，说明没有比查询分数低的学生
                cout << "Nobody" << endl;
            }
        }
    }
    return 0;
}