#include <iostream>
#include <functional>   // std::function 在这个头文件中
using namespace std;    // 这样就可以直接使用 function, cout, endl 等

int main() {
    // function<int(int)> 是一个函数包装器，可以存储任何可调用对象
    // <int(int)> 表示：函数接受一个 int 参数，返回 int
    // 通过 function，lambda 可以递归地引用自身（因为 lambda 本身没有名字）
    function<int(int)> fib = [&fib](int n) -> int {
        return n <= 2 ? 1 : fib(n - 1) + fib(n - 2);
    };

    int n;
    cin >> n;
    cout << fib(n) << endl;   // 输出 5（斐波那契数列第5项：1,1,2,3,5）
    return 0;
}
// function<int(int)> 可以存储任何接受一个 int、返回一个 int 的可调用对象（普通函数、lambda、函数对象等）。
// 为什么这里必须用它？
// 因为 lambda 要递归调用自己。如果写 auto fib = ...，编译器在 lambda 内部还没看到 fib 的定义，会报错。
// 使用 function<int(int)> 后，fib 的类型是明确的，就可以在捕获列表中用 &fib 捕获自己，实现递归。