// 函数模板作为类的友元
#include <iostream>
using namespace std;

class A{
   int v;
public:
   A(int n):v(n) { }   
   
   template <class T>
   friend void Print(const T & p);
};

template <class T>
void Print(const T & p){
 	 cout << p.v;
}

int main()  {
   A a(4);
   Print(a);
   return 0;
}
// 输出：4
// 所有从 template <class T>
// void Print(const T & p)
// 生成的函数，都成为 A 的友元
// 但是自己写的函数  
// void Print(int a) { } 
// 不会成为A的友元