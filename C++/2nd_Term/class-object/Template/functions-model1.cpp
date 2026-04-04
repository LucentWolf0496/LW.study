// 函数模板：只写一个Swap，就能交换各种类型的变量
// 例子如下：template建构模板
// 注意模板的正确使用位置：
// 函数模板的定义语法要求：template <typename ...> 这一行必须直接写在对应的函数定义之前
// 中间不能插入其他非模板的函数或变量定义。
// 在C++模板中，声明类型参数时使用 class 和 typename 完全等价，没有区别。
// 模板还支持非类型参数（如整数、指针等），它们使用具体的类型名（如 int N、char* p），不涉及 class/typename。
#include <iostream>
using namespace std;

template <class T>
void Swap(T & x,T & y) {
	T tmp = x;
	x = y;
	y = tmp;
}

// 函数模板中可以有不止一个类型参数。
// 函数模板中的类型参数也可以用来表示函数模板的返回值类型(print的同时还要返回T2)
template <typename T1, class T2>
T2 print(T1 arg1, T2 arg2){ 
	cout<< arg1 << " " << arg2 << endl;  
	return arg2; // 注意这个函数有返回值！
}

//求数组最大元素的MaxElement函数模板 
template <class T>
T MaxElement(T a[], int size){//size是数组元素个数
	T tmpMax = a[0];
	for( int i = 1;i < size;++i)
		if( tmpMax < a[i] )
			tmpMax = a[i];
	return tmpMax;
}

int main(){
    int n = 1 , m = 2;
    Swap(n , m); // 编译器自动生成 void Swap(int & ,int & )函数
    cout << n << " " << m << endl;
    double f = 1.2 , g = 2.3;
    Swap(f , g); // 编译器自动生成 void Swap(double & ,double & )函数
    double h = print(n , f);// 多个类型的模板于是可以print(int , double)
    cout << h << endl;
    int arr2[5] = {1 , 2 , 333 , 4 , 5};
    cout << MaxElement(arr2 , 5) << endl;
    return 0;
}