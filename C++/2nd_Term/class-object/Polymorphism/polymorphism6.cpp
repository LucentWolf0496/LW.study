// 探索虚函数表
// 使用实验性操作探索底层原理
#include <iostream>
using namespace std;

class A{
	public:	virtual void print() { cout << "A::print" << endl; }
};

class B:public A{
	public:	virtual void print() { cout << "B::print" << endl; }
};

int main(){
	A a;  
    B b;
	A * pa = &b;
	pa->print();
	int *p1 = (int *) pa;    // p1 指向 b 对象的起始地址（即 b 的 vptr）
	int *p2 = (int *) (&a);  // p2 指向 a 对象的起始地址（即 a 的 vptr）
	*p1 = *p2;               // 将 a 的 vptr 值 复制到 b 的 vptr 位置
    // 这里强制把对象地址当作 int*（假设 32 位环境，指针 4 字节；64 位可能需用 long long*，但原理相同）。
    // 执行 *p1 = *p2 后，b 对象的 vptr 被覆盖为 a 对象的 vptr。
    // 现在 b 对象的虚表指针指向的是 A 类的虚函数表。
	pa->print();
    //输出什么？———— B::print  A::print
	return 0;
}