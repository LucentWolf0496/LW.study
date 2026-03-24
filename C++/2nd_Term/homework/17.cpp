#include <iostream>
using namespace std;
class A {
	private:
	int nVal;
	public:
	void Fun()
	{ cout << "A::Fun" << endl; };
	virtual void Do()
	{ cout << "A::Do" << endl; }
};
class B:public A {
	public:
	virtual void Do()
	{ cout << "B::Do" << endl;}
};
class C:public B {
	public:
	void Do( )
	{ cout <<"C::Do"<<endl; }
	void Fun()
	{ cout << "C::Fun" << endl; }
};
void Call(
    A*p// 由于main函数里面有new A，所以只能取基类A，否则取BC就有超越A界限的内容，出错！
) {
	p->Fun(); p->Do();// 还是Fun不是虚函数就去找A，Do是虚函数就去找本来的对象A/C类型
}
int main() {
	Call( new A());
	Call( new C());
	return 0;
}