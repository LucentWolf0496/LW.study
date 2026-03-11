// this指针作用:其作用就是指向成员函数所作用的对象
#include <iostream>
using namespace std;
class Complex {
  public:
    double real, imag;
    void Print() {  cout << real << "," << imag ;  }
    Complex(double r,double i):real(r),imag(i) {	}	
    // 初始化的另一种形式，更加标准————初始化列表形式
    // 又一个标准的初始化示例：CTyre(int r,int w):radius(r),width(w) {   };
    // CCar::CCar(int p,int tr,int w):price(p),tyre(tr, w) {   };
    // 任何生成封闭类对象的语句，都要让编译器明白，对象中的成员对象，是如何初始化的。
    Complex AddOne() {
        this->real ++;   //等价于 real ++;
        this->Print();   //等价于 Print
        return * this;
    } 
};    
struct  A { 	
	 int i;
	 void Hello() { cout << "hello" << endl; } 
};    
int main() {
    Complex c1(1,1),c2(0,0);
    c2 = c1.AddOne();
    A * p = NULL;
  	p->Hello();// 输出：hello————只是调用这个函数，NULL也行，因为函数里面没有NULL相关
               // 这个函数本质是void Hello(A * this) { cout << "hello" << endl; }————所以就算参数是NULL也能输出
               // 但如果函数要用到*this就会报错
    return 0;
} //输出 2,1