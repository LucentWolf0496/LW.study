// 从函数模板到类模板
// 为了便捷地定义出一批相似的类,可以定义类模板,然后由类模板生成不同的类
// 考虑不同元素的数组类：这些数组类，除了元素的类型不同之外，其他的完全相同
// 类模板：在定义类的时候，加上一个/多个类型参数。
// 在使用类模板时，指定类型参数应该如何替换成具体类型，编译器据此生成相应的模板类。

// 编译器由类模板生成类的过程叫类模板的实例化。由类模板实例化得到的类，叫模板类。
// 同一个类模板的两个模板类是不兼容的，但如果都是<string , int>就可以兼容
// Pair<string,int> * p;
// Pair<string,double> a;
// p = &a; 这是错的，不能兼容

// 类模板中可以定义静态成员。从该类模板实例化得到的所有类，都包含同样的静态成员。

#include <iostream>
#include <string>
using namespace std;

template <class T1,class T2>
class Pair{
public:
	T1 key; //关键字
	T2 value; //值
	Pair(T1 k , T2 v):key(k) , value(v) {  };
	bool operator < (const Pair<T1 , T2> & p) const; 
};

template<class T1,class T2>
bool Pair<T1 , T2>::operator < (const Pair<T1 , T2> & p) const { //Pair的成员函数 operator <	
	return key < p.key;    
}

int main(){
    Pair<string , int> * p;
 	Pair<string , int> student("Tom" , 19);// 实例化方式均为<string , int>，允许指针赋值地址，可以兼容
    p = &student; //实例化出一个类 Pair<string,int>，使用<>来完成类型的标记
 	cout << student.key << " " << student.value << endl; 
    cout << p->key << " " << p->value << endl;
 	return 0;
}