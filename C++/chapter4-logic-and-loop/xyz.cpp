//solving the x and y zuixiaogongbeishu
#include <iostream>
using namespace std;

int main()
{
    int x, y, z, w;
    cin >> x >> y;
    if (x < y)
    {
        z = y;
        y = x;
        x = z;
    }
    w = x;
    while (w % y != 0)
    {
        w = w + x;
    }
    cout << w << endl;
    return 0;
}