#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int count = 0 , sum1 = 0 , sum = 0;
    cin >> n;
    for (int i = 1 ; i <= n ; i ++)
    {
        int a = 0 , b = 0;
        cin >> a >> b;
        if (a >= 90 && a <= 140 && b >= 60 && b <= 90)
        {
            count ++;
            sum1 = count;
            if (sum1 >= sum)
            {
                sum = sum1;// sum1的创建是为了保证sum不被每一个正常的小段都更新
                           // 途径：sum1 >= sum才对最终输出的sum赋值
            }
        }
        else
        {
            count = 0;// 如果间断，清空计数
        }
    }
    cout << sum << endl;
    return 0;
}