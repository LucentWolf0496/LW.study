#include <iostream>
#include <cmath>
using namespace std;

// 函数声明
bool isPrime(int n);

int main() 
{
    return 0;
}

// 判断质数的函数
bool isPrime(int n) 
{
    if (n <= 1) 
    {
        return false;
    }
    if (n <= 3) 
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) 
    {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) 
    {
        if (n % i == 0 || n % (i + 2) == 0) 
        {
            return false;
        }
    }
    return true;
}