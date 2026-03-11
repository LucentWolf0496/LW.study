// 计算地铁票价，注意小细节
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() 
{
    int a = 0, b = 0;
    float x = 0.0;
    cin >> a >> b;
    if (a < 100 || a >= 400)// 用或运算，不要粗心！！！
    {
        if (b <= 6)
            x = 3;
        else if (b > 6 && b <= 12)
            x = 4;
        else if (b > 12 && b <= 32)
            x = 4 + ceil ((b - 12) / 10.0);// 1.用cmath扩展+ceil函数免去对恰临界的再次讨论
                                           // 2.注意转浮点运算才能使用ceil，否则就直接变成了取下整的高斯
        else if (b > 32)
            x = 4 + 2 + ceil ((b - 32) / 20.0);
        cout << fixed << setprecision(2) << x << endl;
    }
    else if (a >= 100 && a < 150)
    {
        if (b <= 6)
            x = 3;
        else if (b > 6 && b <= 12)
            x = 4;
        else if (b > 12 && b <= 32)
            x = 4 + ceil ((b - 12) / 10.0);
        else if (b > 32)
            x = 4 + 2 + ceil ((b - 32) / 20.0);
        x = x * 0.8;
        cout << fixed << setprecision(2) << x << endl;
    }
    else if (a >= 150 && a < 400)
    {
        if (b <= 6)
            x = 3;
        else if (b > 6 && b <= 12)
            x = 4;
        else if (b > 12 && b <= 32)
            x = 4 + ceil ((b - 12) / 10.0);
        else if (b > 32)
            x = 4 + 2 + ceil ((b - 32) / 20.0);
        x = x * 0.5;
        cout << fixed << setprecision(2) << x << endl;
    }
    return 0;
}