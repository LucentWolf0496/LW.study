// 类模板作为类模板的友元
#include <iostream>
using namespace std;

template <class T>
class B  {
		T v;
public:
		B(T n):v(n) { }
        
	 template <class T2>
	 friend class A;  
};

template <class T>
class A  {
	public:
		void Func( ) 	{ 
		   B<int> o(10);// 创建一个B类对象，叫做o，初始化v为10
		   cout << o.v << endl;// 有了A是B的友元才能在A中访问B的private类型变量v
		}
};

int main(){
	A< double > a; 
	a.Func ();
	return 0;
}
// 输出：10
// A< double>类，成了B<int>类的友元。
// 任何从A模版实例化出来的类，都是任何B实例化出来的类的友元