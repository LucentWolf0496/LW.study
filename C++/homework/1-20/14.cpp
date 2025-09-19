#include <iostream>
#include <cmath>
using namespace std;

int main() 
{
    int kick = 0;
    int a = 0;
    int x = 0 , y = 0 , z = 0 , w = 0;
    int x1 = 0 , y1 = 0 , z1 = 0;
    int p = 0 , q = 1;
    cin >> kick;
    for (a = 0 ; a <= kick ; a ++)
    {
        x1 = a % 1000;
        x = (a - x1) / 1000;
        y1 = x1 % 100;
         y = (x1 - y1) / 100;
         z1 = y1 % 10;
        z = (y1 - z1) / 10;
        w = a % 10;
        if (a == 10000)
            cout << p << p << p << p << q << endl;
        else if (a >= 1000 && a <= 9999)
        {
            cout << w << z << y << x << endl;
        }
        else if (a >= 100 && a <= 999)
        {
            cout << w << z << y << endl;
        }
        else if (a >= 10 && a <= 99)
        {
            cout << w << z << endl;
        }
        else if (a >= 0 && a <= 9)
        {
            cout << w << endl;
        }
    }
    return 0;
}
