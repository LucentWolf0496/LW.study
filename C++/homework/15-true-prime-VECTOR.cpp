#include <iostream>
#include <cmath>
using namespace std;

bool f1(int); // 判断素数函数f1
int f2(int);  // 倒序函数f2

int main() 
{
    int m = 0 , n = 0;
    cin >> m >> n;
    for (int a = m ; a <= n ; a ++)
    {
        if (f1(a) && f1(f2(a)))
        {
            cout << a << ",";// 用数组将真素数录入，便于输出符合格式的“，”与数的组合
                             // 便于判断尾部逗号添加与否
        }
    }
    return 0;
}

bool f1(int nf) 
{
    for (int i = 2 ; i * i <= nf ; i ++)
    {
        if (nf % i == 0)
        return false;
    }
    if (nf == 1)
        return false;
    return true;
}

int f2(int pf)
{
    // 用数组更便捷地实现倒位
}
