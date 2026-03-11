#include <iostream>
#include <cmath>
using namespace std;

float f1(int , float);
float f2(float);

int main()
{
    float m = 0;
    cin >> m;
    int a = 1 , b = 4;
    float sum1 = 0.0 , sum2 = 0.0;
    float h = (b - a) / m;
    for (int i = 1 ; i <= m - 1 ; i ++)
    {
        sum1 = sum1 + f2(a + i * h) + (a + i * h);
    }
    sum2 = h * (sum1 + (f2(1.0) + f2(4.0) + a + b) / 2.0);
    cout << sum2 << endl;
    return 0;
}

float f1(int x1 , float x)// f2的小部分：泰勒级数各项
{
    long double k = 1;// 要防止k用int溢出！！
                      // int的上界实在是太小了hhh
                      // 法一：硬赋值long double拓宽上界
                      
                      // 法二：迭代计算！！！（better）
    for (int j = 1 ; j <= x1 ; j ++)
    {
        k = k * j;
    }
    float y1 = pow (x , x1) * pow (-1 , x1 / 2) / k;
    return y1;
}

float f2(float x)// 计算cosx-输入x可算
{
    float y = 1e-6 , sum = 1.0;
    int i = 0;
    do
    {
        i ++;
        sum = sum + f1((2 * i) , x);
    } 
    while (abs (f1(2 * i , x)) >= y);
    return sum;
}