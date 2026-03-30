// 多态法一：引用+【.】访问，达成多态，调用引用类型的函数
// 多态法二：指针+【->】指向，达成多态，调用指向类型的函数
#include <iostream>
using namespace std;

class Base {
public:
   virtual Base& fun() { cout << "base fun" << endl; return *this; }
   virtual Base& foo() { cout << "base foo" << endl; return *this; }
};

class Derived: public Base {
public:
   Base& fun() { cout << "derived fun" << endl; return *this; }
   Base& foo() { cout << "derived foo" << endl; return *this; }
};

Base& foo();
Base& fun();
Base x;
Derived y;

Base& foo(){
    cout << "derived foo" << endl;
    return y;
}

Base& fun(){
    cout <<  "base fun" << endl;
    return x;
}

int main() {
   foo().fun().foo();
   fun().foo().fun();
   return 0;
}