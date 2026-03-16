#include <iostream>
using namespace std;

class Complex{
    double real,imag;
public:
	Complex(double r=0,double i=0):real(r),imag(i) { };
	operator double () { return real; } 
	//重载强制类型转换运算符 double
};

int main(){
 	Complex c(1.2,3.4);
 	cout << (double)c << endl; //输出 1.2
 	double n = 2 + c; //等价于 double n=2+c.operator double()
 	cout << n;	//输出 3.2
}