#include <iostream>
#include <cmath>
using namespace std;

int jjj(int);

int main() 
{
    int a = 0;
    int sum = 0;
    cin >> a;
    for (int b = 1 ; b <= a ; b ++)
    {
        sum = sum + jjj(b);
    }
    cout << sum << endl;
    return 0;
}

int jjj(int xf)
{
    int yf = 1;
    for (int i = 1 ; i <= xf ; i ++)
    {
        yf = yf *i;
    }
    return yf;
}