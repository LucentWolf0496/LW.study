#include <iostream> 
using namespace std;
class A { 
	private: 
	int nVal; 
	public: 
	void Fun() 
	{ cout << "A::Fun" << endl; }; 
	void Do() 
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
    B& p// 将c取成B的类型，Fun不是虚函数所以在A里面找输出，Do是虚函数所以输出要在本来的类型C里面去找
) { 
	p.Fun(); p.Do(); 
} 
int main() { 
	C c; 
	Call( c); 
	return 0;
}