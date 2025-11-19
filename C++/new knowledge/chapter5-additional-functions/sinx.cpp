// calculating "sin x"
#include <iostream>
#include <cmath>
using namespace std;

float f1(int , float);

int main()
{
    float x = 0.0 , y = 0.0 , sum = 0.0;
    int i = 0;
    cin >> x >> y;
    do
    {
        i ++;
        sum = sum + f1((2 * i - 1) , x);
    } 
    while (abs (f1(2 * i - 1 , x)) >= y);
    cout << sum << endl;
    return 0;
}

float f1(int x1 , float x)
{
    int k = 1;
    for (int j = 1 ; j <= x1 ; j ++)
    {
        k = k * j;
    }
    float y1 = pow (x , x1) * pow (-1 , (x1 - 1) / 2) / k;
    return y1;
}