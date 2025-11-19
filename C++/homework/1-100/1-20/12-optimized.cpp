#include <iostream>
#include <cmath>
using namespace std;

int main() {// 只要思路清晰，for循环更简单
            // 多多关注题目输入-输出的细节
    int n;
    cin >> n;
    int mid = (n + 1) / 2;
    for (int i = 1; i <= n; i++) {
        int m = abs(i - mid);
        cout << '$';
        for (int j = 0; j < m; j++) {
            cout << ' ';
        }
        for (int j = 0; j < n - 2 * m; j++) {
            cout << '*';
        }
        cout << endl;
    }
    return 0;
}