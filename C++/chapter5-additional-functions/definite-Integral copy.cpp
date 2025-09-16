#include <iostream>
#include <cmath>// 笑死了，这个头文件之下可以直接使用cos（）的函数///
using namespace std;

int main()
{
    float m = 0.0;// 强制措施防止整数除法发生，直接赋值类型为float
    cin >> m;
    int a = 1 , b = 4;
    float sum1 = 0.0 , sum2 = 0.0;
    float h = (b - a) / m;
    for (int i = 1 ; i <= m - 1 ; i ++)
    {
        sum1 = sum1 + cos(a + i * h) + (a + i * h);
    }
    sum2 = h * (sum1 + (cos(a) + cos(b) + a + b) / 2.0);
    cout << sum2 << endl;
    return 0;
}