#include <iostream>
using namespace std;

int main() 
{
    int n = 0;
    cin >> n;
    int day = 0;
    for (int i = 1 ; i <= n ; i ++)
    {
        int year = 0 , month1 = 0 , month2 = 0;
        cin >> year >> month1 >> month2;
        if (month1 > month2)// 改序为1小2大，便于后续统一处理
        {
            int temp = 0;
            temp = month2;
            month2 = month1;
            month1 = temp;
        }
        if ((year % 4 == 0) && (year % 100 != 0) || year % 400 == 0)
        {
            int x[12] = {31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
            // 解决一年月份问题，多设常数数组，表出1-12月的天数即可
            for (int j = month1 - 1 ; j < month2 - 1 ; j ++)
            {
                day = day + x[j];// 细致分析处理相关月经过的天数
            } 
            if (day % 7 == 0)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            day = 0;// 勿忘初始化天数变量从而可以多轮循环
        }
        else// 平年闰年分类讨论
        {
            int x[12] = {31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
            for (int j = month1 - 1 ; j < month2 - 1 ; j ++)
            {
                day = day + x[j];
            } 
            if (day % 7 == 0)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            day = 0;
        }
    }
    return 0;
}