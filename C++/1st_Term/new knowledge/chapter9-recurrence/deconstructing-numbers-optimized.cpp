#include <iostream>
using namespace std;

void f(int &count, int m, int n) {// 取引用count使得可以在主函数中用count计数
    // 从n开始尝试所有可能的因子,通过循环来避免数据的暂时保存问题
    for (int i = n; i * i <= m; i++) {
        if (m % i == 0) {
            count++;  // 找到一种分解：i × (m/i)
            f(count, m / i, i);  // 继续分解剩余部分，从当前因子开始
        }
    }
}

int main() {
    int n = 0;
    cin >> n;
    for (int x = 0; x < n; x++) {
        int m = 0;
        cin >> m;
        int count = 1;  // 包括a=a这种分解
        f(count, m, 2);
        cout << count << endl;
    }
    return 0;
}