#include <iostream>
using namespace std;

int main() 
{
    double a, b;
    cin >> a >> b;
    
    if (a < b) 
    {
        cout << a;
        return 0;
    }
    long long k = (long long)(a / b);// 不用for循环，强制转换类型（将k转化为整数除法得到的整数）
    double r = a - k * b;
    while (r < 0) 
    {
        r += b;
    }
    while (r >= b) 
    {
        r -= b;
    }
    cout << r;
    return 0;
}