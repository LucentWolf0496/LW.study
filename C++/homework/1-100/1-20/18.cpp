#include <iostream>
using namespace std;

int main() 
{
    int a = 0 , b = 0 , d = 0 , e = 1;
    char c = 'c';
    do{
    cin >> a >> b >> c >> d;
    if (a == 0)
    {
        return 0;
    }
    else
    {
        if (d == 1)
        {
            for (int i = 1 ; i <= a ; i ++)
            {
                for (int j = 1 ; j <= b ; j ++)
                {
                    cout << c;
                }
                cout << endl;
            }
        }
        if (d == 0)
        {
            for (int j = 1 ; j <= b ; j ++)
            {
                cout << c;
            }
            cout << endl;
            for (int i = 1 ; i <= a - 2 ; i ++)
            {
                cout << c;
                for (int j = 1 ; j <= b - 2 ; j ++)
                {
                    cout << " ";
                }
                cout << c;
                cout << endl;
            }
            for (int j = 1 ; j <= b ; j ++)
            {
                cout << c;
            }
            cout << endl;
        }
    }
    }while(e == 1);// 卡住循环，直到a == 0时退出，保证多轮键入数据可行
    return 0;
}