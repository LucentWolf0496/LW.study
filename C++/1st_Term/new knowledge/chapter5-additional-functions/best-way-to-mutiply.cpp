#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    if (n % 3 == 0)// 数学本质：全是e最优，但由于整数限制，故全是3对于整数最优
                   // however有微调：4 = 2 * 2 比 4 = 3 * 1 要更好！故余数是1要拎出来单独分析
    {
        int x = n / 3;
        long double y = pow (3 , x);// 防指数爆炸，使用long double赋值确保大数可被表达
        cout << y << endl;
        for (int i = 1 ; i <= x ; i ++)
        {
            cout << 3 << " ";
        }
        cout << "" << endl;
    }
    else if (n % 3 == 1)
    {
        int x = n / 3;
        long double y = pow (3 , x - 1) * 2 * 2;
        cout << y << endl;
        for (int i = 1 ; i <= x - 1 ; i ++)
        {
            cout << 3 << " ";
        }
        cout << 2 << " " << 2 << endl;
    }
    else if (n % 3 == 2)
    {
        int x = n / 3;
        long double y = pow (3 , x) * 2;
        cout << y << endl;
        for (int i = 1 ; i <= x ; i ++)
        {
            cout << 3 << " ";
        }
        cout << 2 << endl;
    }
    return 0;
}
