#include <iostream>
using namespace std;

template <class T>
class A{
public:
    T a;
    A(T x): a(x){  }
	template<class T2>  // 函数模版作为类模板成员
	void Func(T2 t) {cout << t << " " << a << endl;} //成员函数模板
};

template <class T, int size>// 类模板的“<类型参数表>”中可以出现非类型参数
class CArray{
	T array[size];
public:
	void Print(){
 	  	for(int i = 0 ; i < size ; ++ i) cout << array[i] << endl; 
	}
    T & operator[](int x){
        return array[x];
    }			 
};

int main()  {
	A<int> a(5);
	a.Func('K'); // 成员函数模板 Func 被实例化
	a.Func("hello"); // 成员函数模板 Func 再次被实例化
    a.Func("I am a catttttttttt!!!!");

    CArray<double,40> a2;
    CArray<int,50> a3;// a2和a3属于不同的类
    a2[13] = 3.14;
    cout << a2[13] << endl;
	return 0;
}