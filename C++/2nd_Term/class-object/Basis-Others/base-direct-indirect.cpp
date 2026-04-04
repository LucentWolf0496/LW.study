// 直接基类与间接基类
// 类A派生类B，类B派生类C，类C派生类D，……
// 类A是类B的直接基类,类B是类C的直接基类，类A是类C的间接基类,类C是类D的直接基类，类A、B是类D的间接基类

// 在声明派生类时，只需要列出它的直接基类,派生类沿着类的层次自动向上继承它的间接基类
// 派生类的成员包括:
// 派生类自己定义的成员,直接基类中的所有成员,所有间接基类的全部成员
// 派生类对象生成时，基类的构造函数先于派生类的构造函数执行
// 派生类对象消亡时，派生类的析构函数先于基类的析构函数执行
#include <iostream>
using namespace std;
class Base {
	public:
		int n;
		Base(int i):n(i)  {
			cout << "Base " << n << " constructed" 
			<< endl;
		}
		~Base() {
			cout << "Base " << n << " destructed" 
			<< endl;
		}
		
};
class Derived:public Base
{
	public:
		Derived(int i):Base(i) {
			cout << "Derived constructed" << endl;
		}
		~Derived() {
			cout << "Derived destructed" << endl;
		}

};
class MoreDerived:public Derived {
public:
	MoreDerived():Derived(4) {
		cout << "More Derived constructed" << endl;
	}
	~MoreDerived() {
		cout << "More Derived destructed" << endl;
	}
};
int main()
{
	MoreDerived Obj; 
	return 0;
}
