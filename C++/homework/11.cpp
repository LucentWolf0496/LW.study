#include <iostream>
using namespace std;

bool isPrime(int);// 注意声明函数isPrime

int main() 
{   
    int m = 0 , k = 0 , count = 0;// 计数，限制输出
    cin >> m >> k;
    do
    {
        m ++;
        if (isPrime(m))
        {
            cout << m << " ";
            count ++;
        }
    }
    while (count < k - 1);
    do
    {
        m ++;
        if (isPrime(m))
        {
            cout << m << endl;
            count ++;
        }
    }
    while (count < k);
    return 0; // 微调满足题目的刁钻格式
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