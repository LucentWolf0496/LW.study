#include <iostream>
using namespace std;

int main()
{
    float temp = 1.0;
    float x = 0.0 , y = 0.0 , sum = 1.0;
    int n = 0;
    cin >> x >> y;
    while (abs(temp) >= y)// 记住绝对值！绝对值才能保证后续项的正确判断，否则前两项暂时为负数就会终止
    {
        n ++;
        temp = temp * x * x * (-1) / ((2 * n - 1) * (2 * n));// similar递归方式，几乎照搬sinx
        sum +=temp;
    }
    cout << sum << endl;
}