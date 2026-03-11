#include <iostream>
#include <cmath>
using namespace std;

int f1(int);
int f2(int);

int main()
{
    int x = 0;
    cin >> x;
    while (x != 1)
    {
        if (x % 2 == 1)
        {
            x = f1(x);
            cout << x << endl;
        }
        if (x % 2 == 0)
        {
            x = f2(x);
            cout << x << endl;
        }
    }
    return 0;
}

int f1(int x1)
{
    int sum = 3 * x1 + 1;
    return sum;
}

int f2(int x2)
{
    int sum = x2 / 2;
    return sum;
}