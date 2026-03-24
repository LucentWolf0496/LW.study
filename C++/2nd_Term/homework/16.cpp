#include <iostream> 
using namespace std;
class A 
{ 
public:
	A() { }
    virtual ~A(){cout << "destructor A" << endl;}// 虚析构函数使得可以先调用B中析构函数再来A中析构函数
}; 
class B:public A { 
	public: 
	~B() { cout << "destructor B" << endl; } 
}; 
int main() 
{ 
	A * pa; 
	pa = new B; 
	delete pa; 
	return 0;
}