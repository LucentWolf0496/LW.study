// 函数模板可以重载，只要它们的形参表或类型参数表不同即可。
// 函数模板的调用次序：
// 在有多个函数和函数模板名字相同的情况下，编译器如下处理一条函数调用语句
// 1)先找参数完全匹配的普通函数(非由模板实例化而得的函数)。
// 2)再找参数完全匹配的模板函数。
// 3)再找实参数经过自动类型转换后能够匹配的普通函数。
// 4)上面的都找不到，则报错。

// 匹配模板函数时，不进行类型自动转换

#include <iostream>
using namespace std;

template <class T>
T Inc(T n){
	return 1 + n;
}

template<class T1 , class T2>// 重载模板
void print(T1 arg1, T2 arg2) { 
	cout << arg1 << " " << arg2 << endl;  
    cout << "template 1 is used" << endl;
}

template<class T1>// 重载模板
void print(T1 arg1, T1 arg2) { // 注意细节，1&2函数这里是不一样的
	cout << arg1 << " " << arg2 << endl; 
    cout << "template 2 is used" << endl; 
}

// 关于模板函数顺序如下：
template <class T> 
T Max( T a, T b)  {
	cout << "TemplateMax" <<endl;     return 0;
}

template <class T,class T2> 
T Max( T a, T2 b) {
	cout << "TemplateMax2" <<endl;    return 0;
}

double Max(double a, double b){
	cout << "MyMax" << endl;
	return 0;
}

int main(){
    int x = 1;
    double y = 1.0;
    print(x , y);
    print(x , x);
	cout << Inc<double>(5) << " " << Inc<double>(4)/2 << endl; // 不通过参数实例化函数模板,输出 2.5
    // 顺序相关代码如下：
    // 在有多个函数和函数模板名字相同的情况下，编译器如下处理一条函数调用语句
    // 1)先找参数完全匹配的普通函数(非由模板实例化而得的函数)。
    // 2)再找参数完全匹配的模板函数。
    // 3)再找实参数经过自动类型转换后能够匹配的普通函数。
    // 4)上面的都找不到，则报错。
    int i = 4 , j = 5;
    Max(1.2 , 3.4);  // 输出MyMax
    Max(i , j);  //输出TemplateMax
    Max(1.2 , 3); //输出TemplateMax2
    return 0; 
}