// 外设函数递归斐波拉契
#include <iostream>
using namespace std;

int fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    cout << "请输入要计算的斐波那契数列项数: ";
    cin >> n;
    cout << "第" << n << "项斐波那契数是: " << fibonacciRecursive(n) << endl;
    return 0;
}