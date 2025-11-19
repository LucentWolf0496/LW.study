#include <iostream>
using namespace std;

int main()
{
    int fish[5];
    int count = 0;
    for (int i = 6 ; count == 0 ; i += 5)// 一定分清楚=赋值，==判断！
    {
        fish[0] = i;
        for (int k = 1 ; k <= 4 ; k ++)
        {
            fish[k] = 5 * fish[k - 1] / 4.0 + 1;
            if (fish[k] % 5 != 1)
            {
                count = 0;
                break;
            }
            else
                count ++;
        }
        if (count == 4)
        {
            for (int j = 0 ; j <= 4 ; j ++)
            {
                cout << fish[j] << endl;
            }
        }
    }
}