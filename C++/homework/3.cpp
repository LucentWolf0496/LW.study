// 计算邮费
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; i ++)
    {
        float a = 0.0;
        cin >> a;
        char b;
        cin >> b;
        float c = 0.0;
        if (b == 'y')
        {
            if (a <= 1)
            {
                c = 0.8 * a + 2;
                cout << fixed << setprecision(1) << c << endl;
            }
            else
            {
                c = 0.5 * (a - 1.0) + 2.8;
                cout << fixed << setprecision(1) << c << endl;
            }
        }
        else
        {
            if (a <= 1)
            {
                c = 0.8 * a;
                cout << fixed << setprecision(1) << c << endl;
            }
            else
            {
                c = 0.5 * (a - 1.0) + 0.8;
                cout << fixed << setprecision(1) << c << endl;
            }
        }
    }
    return 0;
}