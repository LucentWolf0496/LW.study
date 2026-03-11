// 可以有多个构造函数，参数个数或类型不同 (构造函数的重载)
#include <iostream>
using namespace std;

class Complex {
	private :
 		double real, imag;
	public:
		void Set( double r, double i );
		Complex(double r, double i );
		Complex (double r );
}; 

Complex::Complex(double r, double i){
	real = r; imag = i;
}

Complex::Complex(double r){
	real = r; imag = 0;
}

int main(){
    Complex c1(3) , c2 (1,0);// c1 = {3, 0}, c2 = {1, 0}
}