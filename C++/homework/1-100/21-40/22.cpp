#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 特殊情况：如果输入是0，直接输出0
    if (n == 0) {
        cout << 0;
        return 0;
    }
    
    // 使用数组存储每一位数字
    int digits[5]; // 最大5位数（10000）
    int count = 0;
    
    // 分解整数的每一位数字
    while (n > 0) {
        digits[count] = n % 10;
        n /= 10;
        count++;
    }
    
    // 输出逆序的数字
    for (int i = 0; i < count; i++) {
        cout << digits[i];
    }
    
    return 0;
}