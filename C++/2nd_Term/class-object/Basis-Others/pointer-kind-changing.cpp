// 基类与派生类的指针强制转换
// 公有派生的情况下,派生类对象的指针可以直接赋值给基类指针————Base * ptrBase = &objDerived;
// *ptrBase可以看作一个Base类的对象，访问它的public成员直接通过ptrBase即可
// 但不能通过ptrBase访问objDerived对象中属于Derived类而不属于Base类的成员

// 即便基类指针指向的是一个派生类的对象，也不能通过基类指针访问基类没有，而派生类中有的成员。
// 通过强制指针类型转换，可以把ptrBase转换成Derived类的指针
#include <iostream>
using namespace std;

class Base {
	protected:	
		int n;
	public:
		Base(int i):n(i){ cout << "Base " << n << " constructed" << endl; }
		~Base() { cout << "Base " << n << " destructed" << endl; }
		void Print() { cout << "Base:n=" << n << endl; }
};

class Derived:public Base  {
	public:
		int v;
		Derived(int i):Base(i),v(2 * i) { cout << "Derived constructed" << endl; }
		~Derived() 	{ cout << "Derived destructed" << endl;}
		void Func() { } ;
		void Print() { 
			cout << "Derived:v=" << v << endl;
			cout << "Derived:n=" << n << endl;
		}
};

int main()  {  	
	Base objBase(5);
	Derived objDerived(3); 
   	Base * pBase = & objDerived ;
	//pBase->Func(); //err;Base类没有Func()成员函数
	//pBase->v = 5; //err; Base类没有v成员变量
	pBase->Print(); 
	//Derived * pDerived = & objBase; //error
	Derived * pDerived = (Derived *)(& objBase); 
	pDerived->Print();  //慎用，可能出现不可预期的错误
	pDerived->v = 128; //往别人的空间里写入数据，会有问题
	objDerived.Print();
	return 0;
}