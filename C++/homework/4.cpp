// 输入n个数，计算它们除了最大数的加和
#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int a = 0, b = 0, c = 0;
    cin >> n;
    for (int i = 1; i <= n; i ++)
    {
        cin >> a;
        if (a > c)
        {
            b = b + c;
            c = a;
        }
        if (a < c)
        {
            b = b + a;
        }
        if (a = c)
        {
            c = a;
        }
    }
    cout << b << endl;
    return 0;
}