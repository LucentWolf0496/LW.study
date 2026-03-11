#include <iostream>
using namespace std;

int main()
{
    int x1 = 0;
    cin >> x1;
    int bad[21];
    for (int i = 1 ; i <= x1 ; i ++)
    {
        for (int m = 0 ; m < 21 ; m ++)
        {
            bad[m] = -1;
        }
        int x2 = 0 , sum = 0 , count = 0 , thu = 0;
        cin >> x2;
        for (int j = 0 ; j < x2 ; j ++)
        {
            int x3 = 0;
            cin >> x3;
            bad[j] = x3;
        }
        for (int k = 0 ; k < 21 ; k ++)
        {
            if (bad[k] != -1)
                count ++;
        }
        int time = 0;
        for (int k = 1 ; k <= count ; k ++)
        {
            time = bad[k - 1] + 3 * (k - 1);
            if (time > 60){
                sum = 60 - 3 * (k - 1);
                thu = 1;
                break;
            }
            else if (time <= 60 && time > 57){
                sum = bad[k - 1];
                thu = 1;
                break;
            }
        }
        if (thu == 0)
        {
            sum = 60 - count * 3;
        }
        cout << sum << endl;
    }
    return 0;
}