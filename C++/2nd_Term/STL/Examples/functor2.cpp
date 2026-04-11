#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

int main() {
    std::vector<int> v = {1, 2, 3, 4};

    // 1. 默认求和：1+2+3+4 = 10
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << sum << '\n';

    // 2. 使用 plus 函数对象（效果同上）
    int sum2 = std::accumulate(v.begin(), v.end(), 0, std::plus<int>());

    // 3. 计算乘积：1*2*3*4 = 24————这个时候初始就应该是1而不是0，否则永远无法乘起来
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

    // 4. 使用 greater 统计大于 2 的元素个数————lambda表达式
    int cnt = std::accumulate(v.begin(), v.end(), 0,
        [](int acc, int x) { return acc + (x > 2 ? 1 : 0); });
    // 或者用函数对象配合绑定，但通常 lambda 更简洁
    // Lambda 表达式是 C++11 引入的语法糖，用于就地定义 匿名函数对象（即仿函数）。
    // 编译器遇到 lambda 表达式时，会将其转换为一个未命名的类类型（closure type），并生成该类的对象。
    // std::accumulate 的第四个参数是一个 可调用对象（Callable），可以是函数指针、函数对象或 lambda。
    // 这就是面向对象的强大之处！！甚至可以用来建构语法糖lambda！！
    std::cout << cnt; // 2
}