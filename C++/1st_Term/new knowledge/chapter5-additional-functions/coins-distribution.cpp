#include <iostream>
#include <cmath>
using namespace std;

bool f1(int , int , int);

int main()
{
    int count = 0;
    for (int z = 0 ; z <= 2 ; z ++)
        for (int y = 0 ; y <= 5 ; y ++)
            for (int x = 0 ; x <= 10 ; x ++)// 改序列，满足题目要求
            {
                if (f1(x , y , z))
                {
                    count ++;
                    cout << count << " " << x << " " << y << " " << z << endl;
                }
            }
    return 0;
}

bool f1(int x1 , int y1 , int z1)
{
    if (x1 + 2 * y1 + 5 * z1 == 10)
        return true;
    else
        return false;
}