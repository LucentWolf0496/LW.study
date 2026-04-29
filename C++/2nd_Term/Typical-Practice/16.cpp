#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

class MyMap{

    map<int, vector<string>> data;
public:
    friend istream& operator>>(istream& is, MyMap& mm) {
        string name; int score;
        is >> name >> score;
        mm.data[score].push_back(name);
        return is;
    }
    friend ostream& operator<<(ostream& os, const MyMap& mm) {
        for (auto it = mm.data.rbegin(); it != mm.data.rend(); ++it) {
            vector<string> v = it->second;
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            /*unique(v.begin(), v.end())
            头文件：<algorithm>
            作用：对区间 [v.begin(), v.end()) 进行 压缩，将 每一组连续相等的元素 只保留第一个，其余重复的元素 移动到区间的尾部。
            返回值：一个迭代器 new_end，指向 去重后逻辑区间的尾后位置（即第一个被移动到尾部的重复元素的位置）。*/
            // 需要排序后再使用unique，只对相邻元素去重
            os << it->first;
            for (const auto& s : v) os << " " << s;
            os << endl;
        }
        return os;
    }

};
int main()
{
    int n;
    cin >> n;
    MyMap mm;
    for (int i = 0; i < n; ++i)
        cin >> mm;
    cout<<mm;
    return 0; 
}