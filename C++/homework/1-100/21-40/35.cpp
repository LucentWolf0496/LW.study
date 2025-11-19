#include <iostream>
#include <vector>
using namespace std;

int main()
{
    do
    {
        int n = 0;
        int count = 1 , r = 0;
        cin >> n;
        if (n == 0)
            return 0;
        vector<int> num;
        for (int i = 0 ; i < n ; i ++)
        {
            int x = 0;
            cin >> x;
            num.push_back(x);// 注意标准的vector加入元素的语言表达！
        }
        for (int i = 0 ; i < n ; i ++)
        {
            int temp = 0;
            int s = 0;
            temp = num[i];
            s = i;
            while(num[i + 1] == temp && i <= n - 2)// 限定一下i的最大值防止溢出！
                                                   // 确保num数组方括号内有意义！
            {
                count ++;
                i ++;
            }
            i = s;
            if (count > r)
                r = count;
            count = 1;
        }
        cout << r << endl;
    }
    while(true);
    return 0;
}