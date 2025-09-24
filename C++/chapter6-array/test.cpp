#include <iostream>
using namespace std;

int main()
{
    char shuzi[] = "987654321";// 零基数组，0-8号对应9-1
                               // 注意9号是“/0”
    int count = 0;
    char *p = &shuzi[8];// 指针指向8号位也就是字符“1”的地址
    do
    {
        cout << *p;
        p --;// 指针位置一直在数组中-1，相当于是从后往前遍历
        count ++;
    }
    while (p >= shuzi);// shuzi作为常量指针，是0号的地址，也就是遍历直到0号就终止
    cout << endl;
    cout << count << endl;
    return 0;
}