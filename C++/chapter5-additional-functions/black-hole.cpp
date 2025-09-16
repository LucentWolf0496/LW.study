// 数字黑洞6174，对于并非四个相同数码的四位数全部成立！
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

int f1(int);
int f2(int , int , int, int);
int f3(int , int , int, int);

int main()
{
    int x = 0 , y = 0;
    cin >> x;
    do
    {
        y = x;
        x = f1(x);
    } 
    while (x != y);
    cout << x << endl;
    return 0;
}

int f1(int x1)
{
    int a = x1 % 10;
    x1 /= 10;
    int b = x1 % 10;
    x1 /= 10;
    int c = x1 % 10;
    x1 /= 10;
    int d = x1 % 10;
    int max = f2(a , b , c ,d);
    int min = f3(a , b , c ,d);
    return (max - min);
}

int f2(int a , int b , int c , int d)
{
    vector<int> digits = {a, b, c, d};
    sort(digits.begin(), digits.end(), greater<int>());
    int maxNumber = 0;
    do 
    {
        int current = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
        if (current > maxNumber && current >= 1000) // 上限有必要保证
        {
            maxNumber = current;
        }
    } 
    while (prev_permutation(digits.begin(), digits.end()));
    return maxNumber;
}

int f3(int a , int b , int c , int d)
{
    vector<int> digits = {a, b, c, d};
    sort(digits.begin(), digits.end(), greater<int>());
    int minNumber = 10000;// 微调，max是和小数比大，min改为和大数比小
    do 
    {
        int current = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
        if (current < minNumber) // 解除下限，确保1000可算
        {
            minNumber = current;
        }
    } 
    while (prev_permutation(digits.begin(), digits.end()));
    return minNumber;
}