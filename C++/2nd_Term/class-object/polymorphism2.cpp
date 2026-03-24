// 多态的简单示例:
// 派生类的指针可以赋给基类的指针，派生类的对象可以赋给基类的引用
// 基类只用管派生类中属于基类的部分就好了
#include <iostream>
using namespace std;
class A { 
	public:  	
	virtual  void Print(  ) {   cout << "A::Print" << endl ; }
};
class B: public A { 
	public:  	
	virtual  void Print(  ) {   cout << "B::Print" << endl ; }
};
class D: public A {	  
	public: 
	virtual  void Print(  ) {   cout << "D::Print" << endl ; }
};
class E: public B { 
	public: 
	virtual  void Print(  ) {   cout << "E::Print" << endl ; }
};

int main()  {
    A a; 
    B b;
    D d;
    E e;
    A * pa = &a;
    B * pb = &b;    
    D * pd = &d;
    E * pe = &e;  

    pa->Print();     
    pa = pb;         
    pa -> Print();   
    pa = pd;
    pa -> Print();   
    pa = pe;
    pa -> Print();   
    return 0;
}