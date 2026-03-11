#include <iostream>
#include <cmath>
using namespace std;

// 使用三元运算符的简洁版本
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b;
    
    cout << "输入两个整数: ";
    cin >> a >> b;
    
    cout << "GCD(" << a << ", " << b << ") = " << gcd(abs(a), abs(b)) << endl;
    
    return 0;
}