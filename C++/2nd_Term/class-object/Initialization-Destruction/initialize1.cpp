// 构造函数最好是public的，private构造函数不能直接用来初始化对象
#include <iostream>
using namespace std;

class Complex {
	private :
 		double real, imag;
	public:
		Complex( double r, double i = 0);
}; 

Complex::Complex( double r, double i) { // public的构造函数，最关键，最需要理解的部分！！！————但这样写实则不好，应该用
                                        // Complex (double r , double i): real(r) , imag(i) { }
	real = r; imag = i;
}

int main(){
    //Complex c1;  // error, 缺少构造函数的参数
    //Complex * pc = new Complex; // error, 没有参数
    Complex c1(2); // OK
    Complex c1(2,4), c2(3,5);
    Complex * pc = new Complex(3,4);
}