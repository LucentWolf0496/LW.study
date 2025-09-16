#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int);

int main() 
{
    return 0;
}

bool isPrime(int nf) 
{
    for (int i = 2 ; i * i <= nf ; i ++)
    {
        if (nf % i == 0)
        return false;
        
    }
    if (nf == 1)
        return false;// 完善1不是素数
    return true;
}