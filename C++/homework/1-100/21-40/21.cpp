#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n = 0;
    int x1 = 0 , x2 = 0 , x3 = 0 , x4 = 0 , x5 = 0 ;
    int max = 0 , min = 0;
    cin >> n;
    int num[n];
    for (int i = 0 ; i <= n - 1 ; i ++)
    {
        int x = 0;
        cin >> x;
        num[i] = x;
    }
    x4 = abs(num[0]);
    x5 = abs(num[0]);// 要先定义数组再拿数值填充！
    for (int i = 0 ; i <= n - 1 ; i ++)
    {
        if (num[i] > 0)
            x1 ++;
        else if (num[i] < 0)
            x2 ++;
        x3 = x3 + num[i];
        if (abs(num[i]) >= x4)
        {
            x4 = abs(num[i]);
            max = i;
        }
        else if (abs(num[i]) <= x5)
        {
            x5 = abs(num[i]);
            min = i;
        }
    }
    cout << x1 << endl;
    cout << x2 << endl;
    cout << x3 << endl;
    cout << num[max] << endl;
    cout << num[min] << endl;
}