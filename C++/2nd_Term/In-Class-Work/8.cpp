#include <iostream>
#include <map>
using namespace std;

class A {
public:
    static int count;
    A() { count++; }
    A(int) { count++; }
    A(const A&) { count++; }// func(b1)时调用
    virtual ~A() { count--; cout << "A::destructor" << endl; }
};

class B : public A {
public:
    B(int n) : A(n) {}
    B(const B& b) : A(b) {}// func(b1)时调用,需要拷贝生成临时量传入func作为参数
    ~B() { cout << "B::destructor" << endl; }
};

int A::count = 0;
void func(B b) {  }
int main()
{
	A a1(5),a2;
	cout << A::count << endl;
	B b1(4);
	cout << A::count << endl;
	func(b1);
	cout << A::count << endl;
	A * pa = new B(4);
	cout << A::count << endl;
	delete pa;
	cout << A::count << endl;
	return 0;
}