// 运算符重载，就是对已有的运算符(C++中预定义的运算符)赋予多重的含义，使同一运算符作用于不同类型的数据时导致不同类型的行为。
// 运算符重载的目的是：扩展C++中提供的运算符的适用范围，使之能作用于对象。而不仅仅作用于整数
// 同一个运算符，对不同类型的操作数，所发生的行为不同。
// 行为1————complex_a + complex_b   生成新的复数对象
// 行为2————5 + 4 = 9

// 运算符重载的实质是函数重载
// 运算符被多次重载时，根据实参的类型决定调用哪个运算符函数。
// 如果将 [ ] 运算符重载成一个类的成员函数，则该重载函数有1个参数————*this
#include <iostream>
using namespace std;

class Complex {
    public:
        double real,imag;    
        Complex( double r = 0.0, double i= 0.0 ):real(r),imag(i)   {     }
        Complex operator-(const Complex & c); // 记得取引用，只有一个参数是因为另一个参数被包含在类里面
};

Complex operator+( const Complex & a, const Complex & b){
	return Complex( a.real+b.real,a.imag+b.imag); //返回一个临时对象
} 

Complex Complex::operator-(const Complex & c){
 	return Complex(real - c.real, imag - c.imag); //返回一个临时对象
}// 写全局函数+或者类中的函数-都是可以的

class Array {// 对[]重载
private:
    int data[10];
public:
    int& operator[](int idx) { // 返回引用，允许赋值
        return data[idx];
    }
};

int main(){
 	Complex a(4,4),b(1,1),c;
 	c = a + b; //等价于c=operator+(a,b);
 	cout << c.real << "," << c.imag << endl;
 	cout << (a-b).real << "," << (a-b).imag << endl;
	//a-b等价于a.operator-(b)
	
	Array arr;
    arr[2] = 42;               // 调用 operator[]，写入值
    std::cout << arr[2];        // 读取值
 	return 0;
}