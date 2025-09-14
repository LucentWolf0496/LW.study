// 迭代法解斐波拉契
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n = 0;
    int a = 0;
    int x = 1, y = 1, z = 0;// 迭代思路：找空变量暂时容纳和，then可以实现：
                            // 一个“循环”被成功创建，滚滚向前！！！
    cin >> n;
    for (int i = 1 ; i <= n ; i ++)
    {
        cin >> a;
        if (a == 1 || a == 2)
            cout << 1 << endl;
        else if (a >= 3)
        {
            for (int j = 1 ; j <= a - 2 ; j ++)
            {
                z = x + y;
                x = y;
                y = z;
            }
            cout << z << endl;
            x = 1;
            y = 1;
            z = 0;
        }
        
    }
    return 0;
}