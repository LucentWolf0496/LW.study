#include <iostream>
using namespace std;

int main()
{
    for (int i = 100 ; i <= 999 ; i ++)
    {
        int n = i;
        int a = n % 10;
        n /= 10;
        int b = n % 10;
        n /= 10;
        int c = n % 10;
        if (a * a * a + b * b * b + c * c * c == i)
            cout << i << endl;
    }
}