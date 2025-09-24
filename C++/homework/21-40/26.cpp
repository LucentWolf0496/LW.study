#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n = 0 ;
    double sum = 0.0;
    cin >> n;
    double arr[n + 1];// n个序列值需要n+1个斐波拉契数列值
    double x = 1.0 , y = 1.0 , z = 0.0;
    for (int i = 1 ; i <= n + 1 ; i ++)// 应该计算到arr[n]才行
    {
        z = x;
        y = x + y;
        x = y;
        y = z;
        arr[i - 1] = y;
    }
    for (int j = 1 ; j <= n ; j ++)
    {
        double x = 0.0;
        x = (arr[j] + 0.0) / arr[j - 1];// 这里要用到arr[n]
        sum = sum + x;
    }
    cout << fixed << setprecision(4) << sum << endl;
}