#include <iostream>
#include <vector>
#include <algorithm>   // 补充：用于 min_element 和 max_element
using namespace std;

// 在此处补充你的代码
// 情况0: 显式指定比较器类型（如 less<int>），使用 max_element + 默认构造的比较器对象
template<typename Iter, typename Comp>
typename Iter::value_type getWanted(Iter first, Iter last) {
    return *std::max_element(first, last, Comp());
}
// typename 在模板内部、用于依赖名字之前时，就是一个“显式声明该名字为类型”的标志
// 在本代码中就被转化为int，其实可以将所有的typename Iter::value_type写成int

// 情况3: 无比较器，求最小值
template<typename Iter>
typename Iter::value_type getWanted(Iter first, Iter last) {
    return *std::min_element(first, last);
}

// 情况1和2: 带比较器对象的版本，求最大值（按给定比较规则）
template<typename Iter, typename Comp>
typename Iter::value_type getWanted(Iter first, Iter last, Comp comp) {
    return *std::max_element(first, last, comp);
}

struct myComp {
    bool operator ()(int a, int b) {
        return a % 10 < b % 10;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> a, b, c;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    int cmd;
    while (cin >> cmd) {
        switch (cmd) {
            case 0:
                cout << getWanted<vector<int>::iterator, less<int>>(a.begin(), a.end()) << endl;
                break;
            case 1:
                cout << getWanted<vector<int>::iterator>(a.begin(), a.end(), less<int>()) << endl;
                break;
            case 2:
                cout << getWanted<vector<int>::iterator>(a.begin(), a.end(), myComp()) << endl;
                break;
            case 3:
                cout << getWanted<vector<int>::iterator>(a.begin(), a.end()) << endl;
                break;
        }
    }
    return 0;
}