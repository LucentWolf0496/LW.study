#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Complex{
    private:
        int real;
        int imag;
    public:
        Complex() {  }
        ~Complex() {  }
        Complex(int r , int i):real(r) , imag(i) {  }
        Complex(const Complex & x):real(x.real) , imag(x.imag){  }
        operator int() { return real * real + imag * imag; }
        operator double() { return sqrt(real * real + imag * imag); }
        Complex operator++(int);
        Complex & operator++();
        Complex operator--(int);
        Complex & operator--();
        Complex & operator=(const Complex & x);
        friend Complex operator+(const Complex & x , const Complex & y);
        friend Complex operator+(const Complex & x , int y);
        friend Complex operator+(int x , const Complex & y);
        friend Complex operator*(const Complex & x , const Complex & y);
        friend ostream & operator<<(ostream & os , const Complex & x);
};

Complex & Complex::operator++(){
    real ++;// 直接先增加
    return *this;// 返回已经被增加过的新值
}

Complex & Complex::operator--(){
    real --;
    return *this;
}

Complex Complex::operator++(int){
    Complex temp(*this);// 保存旧值为临时变量
    real ++;// 更改值，增加1
    return temp;// 返回旧的临时变量
}

Complex Complex::operator--(int){
    Complex temp(*this);
    real --;
    return temp;
}

Complex & Complex::operator=(const Complex & x){
    real = x.real;
    imag = x.imag;
    return *this;
}

Complex operator+(const Complex & x , const Complex & y){
    Complex temp(x.real + y.real , x.imag + y.imag);
    return temp;
}

Complex operator+(const Complex & x , int y){
    Complex temp(x.real + y , x.imag);
    return temp;
}

Complex operator+(int x , const Complex & y){
    Complex temp(x + y.real , y.imag);
    return temp;
}

Complex operator*(const Complex & x , const Complex & y){
    int real0 = y.real * x.real - y.imag * x.imag;
    int imag0 = y.real * x.imag + y.imag * x.real;
    Complex temp(real0 , imag0);
    return temp;
}

ostream & operator<<(ostream & os , const Complex & x){
    if (x.imag >= 0) os << x.real << "+" << x.imag << "i";
    else os << x.real << x.imag << "i";
    return os;
}

int main(){
    Complex list[2];
    vector<Complex> list0(2);
    Complex c1(5 , 4);
    Complex c2(4 , 6);
    Complex c3;
    c3 = c1 * c2;
    cout << c1 << " " << c2 << " " << c3 << endl;
    cout << int(c1) << " " << double(c1) << endl;
    cout << c1 + c2 << " " << c1 + 3 << " " << 3 + c1 << endl;
    cout << c1++++++ << endl;// 后置：先复制后增加值，不能连续使用，连续使用本质上是在对临时变量操作。无效！
    cout << c1 << endl;// 只被累加了一次————后置本质是返回旧的临时变量后再累加自身，所以后置不能取引用，是因为临时变量不能取&引用
                       // 临时变量只能取const &的引用
    cout << ++++++c1 << endl;// 前置：直接增加值，无需复制，更高效 **可以连续使用
    cout << c1 << endl;// 被累加了三次
}