#include <iostream>
using namespace std;

int main() 
{
    int n;
    cin >> n;
    
    // 处理特殊情况：输入为0
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    // 逆序输出数字
    while (n > 0) {
        cout << n % 10; // 获取最后一位数字
        n /= 10;        // 去掉最后一位数字
    }
    cout << endl;
    
    return 0;
}