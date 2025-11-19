#include <iostream>
using namespace std;

int main()
{
    int w = 0;
    cin >> w;
    int month[12] = {31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
    for (int i = 0 ; i < 12 ; i ++)// 应该包含month[11]，也就是12月在数组之中
                                   // 因为w是在最后加上，就算用不上12月也没关系
                                   // 但是12月是要用i=11去判断的！
    {
        if ((w + 12) % 7 == 5)
            cout << i + 1 << endl;
        w = (w + month[i]) % 7;
    }
    cout << endl;
    return 0;
}