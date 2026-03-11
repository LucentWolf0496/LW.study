//test a range of different ways of enpowering numbers
#include <iostream>
using namespace std;

int main()
{
    int i;      // 声明一个整型变量
    long m;     // 声明一个长整型变量
    float f;    // 声明一个单精度浮点型变量
    double d;   // 声明一个双精度浮点型变量
    
    // 输出int类型的大小、变量i的大小以及变量i的地址
    cout << "sizeof(int)=" << sizeof(int) << ", sizeof(i)=" << sizeof(i) << ", &i=" << &i << endl;
    
    // 输出long类型的大小、变量m的大小以及变量m的地址
    cout << "sizeof(long)=" << sizeof(long) << ", sizeof(m)=" << sizeof(m) << ", &m=" << &m << endl;
    
    // 输出float类型的大小、变量f的大小以及变量f的地址
    cout << "sizeof(float)=" << sizeof(float) << ", sizeof(f)=" << sizeof(f) << ", &f=" << &f << endl;
    
    // 输出double类型的大小、变量d的大小以及变量d的地址
    cout << "sizeof(double)=" << sizeof(double) << ", sizeof(d)=" << sizeof(d) << ", &d=" << &d << endl;
    
    return 0;
}