// 输出是k的倍数的数组
#include <iostream>
using namespace std;

int main()
{
    int m = 0, n = 0, k = 0, x = 0;
    cin >> m >> n >> k;
    for (int ai = m; ai <= n; ai ++)
        for (int bi = m; bi <=n; bi ++)
        {
            if (ai >= bi) continue;
            if ((ai + bi) % k == 0)
            {
                cout << "(" << ai << "," << bi << ")" << endl;
                x ++;
            }
        }
    if (x == 0)
        cout << "no" << endl;
    return 0;
}