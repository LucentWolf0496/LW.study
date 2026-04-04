// 纯虚函数和抽象类
// 包含纯虚函数的类叫抽象类
// 抽象类只能作为基类来派生新类使用，不能创建抽象类的对象
// 抽象类的指针和引用可以指向由抽象类派生出来的类的对象
// A a ;             错，A 是抽象类，不能创建对象
// A * pa ;          ok,可以定义抽象类的指针和引用
// pa = new A ;      错误, A 是抽象类，不能创建对象
// 在抽象类的成员函数内可以调用纯虚函数，但是在构造函数或析构函数内部不能调用纯虚函数。
// 如果一个类从抽象类派生而来，那么当且仅当它实现了基类中的所有纯虚函数，它才能成为非抽象类。
#include <iostream>
using namespace std;

class A {
	public:
	virtual void f() = 0; //纯虚函数————特点是后缀写上“= 0”
	void g( ) { 	this->f( ) ; //ok
	}
	A( ){   //f( ); // 错误
	}
};
class B:public A{
public:
	void f(){cout<<"B:f()"<<endl; }
};
int main(){
	B b;
	b.g();
	return 0;
}
