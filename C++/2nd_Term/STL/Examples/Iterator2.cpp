// vector / list 遍历示例
// vector 的迭代器是随机访问迭代器，支持下标、比较大小、加减运算。
// list 的迭代器是双向迭代器，不支持下标、不支持 < 比较，也不支持加减整数。

#include <iostream>
#include <vector>
#include <list>
using namespace std;   // 引入标准库命名空间

int main() {
    // ========== vector 部分 ==========
    vector<int> v(100);

    // 1. 使用下标访问（适用于随机访问迭代器）
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
    }
    cout << endl;

    // 2. 使用迭代器， != 比较
    vector<int>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it) {
        cout << *it;
    }
    cout << endl;

    // 3. 使用迭代器， < 比较（也合法，因为随机访问迭代器支持 <）
    for (it = v.begin(); it < v.end(); ++it) {
        cout << *it;
    }
    cout << endl;

    // 4. 间隔一个输出（使用 while 和迭代器加法）
    it = v.begin();
    while (it < v.end()) {
        cout << *it;
        it = it + 2; // 随机访问迭代器支持加整数
    }
    cout << endl;

    // ========== list 部分 ==========
    list<int> lst;
    // 为了演示，向 list 中添加一些元素
    for (int i = 0; i < 10; ++i) {
        lst.push_back(i);
    }

    // 正确的遍历方式：使用 != 比较，并且只能 ++ 或 --
    list<int>::const_iterator lit;
    for (lit = lst.begin(); lit != lst.end(); ++lit) {
        cout << *lit;
    }
    cout << endl;

    // 错误的做法（被注释掉，若取消会编译失败）：
    /*
    // 错误1：双向迭代器不支持 < 比较
    for (lit = lst.begin(); lit < lst.end(); ++lit) {
        cout << *lit;
    }

    // 错误2：list 没有下标运算符 []
    for (size_t i = 0; i < lst.size(); ++i) {
        cout << lst[i];
    }

    // 错误3：双向迭代器不支持加法（如 lit + 2）
    lit = lst.begin();
    while (lit < lst.end()) {
        cout << *lit;
        lit = lit + 2;
    }
    */

    return 0;
}