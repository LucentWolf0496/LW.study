// 对类进行运算符重载使得Algorithm算法可以被运用于对象之上————通常是重载>,<,==三个运算符
// 代码样例如下，涉及对类A的运算符重载
#include <iostream>
#include <algorithm>
using namespace std;
class A{
    int v;
    public:
        A(int n):v(n) { }
        bool operator < (const A & a2) const{ 
		//必须为常量成员函数————因为binary_search内置的是常量函数引用，如果不是常量会产生冲突
  		    cout << v << "<" << a2.v << "?" << endl;
	  	    return false;// 这个逻辑其实有问题，不可能无脑返回false，所以这个代码仅作展示使用
        }	
        bool operator ==(const A & a2) const{
	 	    cout << v << "==" << a2.v << "?" << endl;
		    return v == a2.v;
        }
};

int main(){
 	A a [] = { A(1),A(2),A(3),A(4),A(5) };
 	cout << binary_search(a , a + 4 , A(9));  //折半查找，定义在algorithm中，需要用到运算符<
 	return 0;
}