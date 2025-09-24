#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    vector<bool> light(n , true);// 定义时使用圆括号，采用全部定义为true的方式
                                 // 逐个定义则使用大括号和内部逗号分隔
    for (int i = 1 ; i <= n ; i ++)
    {
        int k = 1;
        do
        {
            if (light[i * k - 1])// 仅在抓取单个元素的时候使用方括号！！！
                light[i * k - 1] = false;
            else if (!light[i * k - 1])
                light[i * k - 1] = true;
            k ++;
        }
        while(k * i <= n);
    }
    for (int i = 1 ; i <= n ; i ++)
    {
        if (light[i - 1])
            cout << i << " ";
    }
    cout << endl;
    return 0;
}