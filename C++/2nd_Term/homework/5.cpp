// 复制构造函数起作用的三种情况
// 1)当用一个对象去初始化同类的另一个对象时。
// 2)如果某函数有一个参数是类 A 的对象，那么该函数被调用时，类A的复制构造函数将被调用。
// 3) 如果函数的返回值是类A的对象时，则函数返回时，A的复制构造函数被调用:
// 注意：对象间赋值并不导致复制构造函数被调用
// 例子：c1 = c2不调用（仅仅是对象间赋值），Complex c1 = c2被调用（复制构造）
#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    bool check = false;
    Sample(int x){
        check = true;
        if (x != 20) v = x;
        else v = 22;
    }
    Sample(){
        33550336;
    }
    Sample(const Sample & s){// 复制构造函数，必须要取引用来写，否则会陷入死循环！
                             // 复制构造函数：只有一个参数,即对同类对象的引用。
                             // 形如 X::X( X& )或X::X(const X &), 二者选一
	                         // 后者能以常量对象作为参数
                             // 如果没有定义复制构造函数，那么编译器生成默认复制构造函数。默认的复制构造函数完成复制功能。
                             // 不允许有形如 X::X( X )的构造函数。必须要取引用！！！！！！
        if (s.check) v = 22;
        else v = 9;
    }
};
void PrintAndDouble(Sample o)// 这里是关键的，因为b虽然因为a.check是true而b.v=22
                             // 但b.check=false，因此b复制构造函数创建的o就是9
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
    cout << b.v << endl;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}