#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int);

int main()
{
    int m = 0;
    cin >> m;
    for (int i = 2 ; i <= m - i ; i ++)
    {
        if (isPrime (i) && isPrime (m - i))
            cout << i << " " << (m - i) << endl; 
    }
    return 0;
}

bool isPrime(int nf) 
{
    for (int i = 2 ; i * i <= nf ; i ++)
    {
        if (nf % i == 0)
        return false;
    }
    return true;
}